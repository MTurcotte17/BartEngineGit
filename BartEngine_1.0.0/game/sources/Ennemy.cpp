#include <Assets.h>
#include <Ennemy.h>
#include <TileMap.h>
#include <TileLayer.h>
#include <iostream>
#include <LevelOneMap.h>
#include <OiseauManager.h>

Ennemy::Ennemy()
{
	m_Transform = new Transform;
	m_EnnemySprite = new Sprite;
}

void Ennemy::Draw()
{
	m_EnnemySprite->Draw();
}

void Ennemy::Update(float aDeltaTime)
{
	LevelOneMap* tEntity = static_cast<LevelOneMap*>(Engine::Instance().GetScene().FindEntity("LevelOne"));
	TileMap* tMap = tEntity->GetMap();
	TileLayer* tLayer = tMap->GetLayer<TileLayer>("Collision");

	switch(m_CurrentState)
	{
		case Grounded:
		{
			GroundedUpdate(aDeltaTime);
			break;
		}
		case Flapping:
		{
			FlappingUpdate(aDeltaTime);
			break;
		}
		case Falling:
		{
			FallingUpdate(aDeltaTime);
			break;
		}
		case Parachuting:
		{
			ParachutingUpdate(aDeltaTime);
			break;
		}
	}

	if (m_CurrentState != Grounded)
	{
		m_HorizontalVelocity += m_Speed;
		m_VerticalVelocity += m_VelocityDecayRate;
	}

	



	m_Destination.Y = static_cast<int>(m_Transform->Y);
	if (tLayer != nullptr)
	{

		m_Destination.Y = static_cast<int>(m_Transform->Y);
		if (tLayer->IsColliding(m_Destination) != 0)
		{
			if (m_Destination.Y < m_OldY)
			{
				m_VerticalVelocity = (m_VerticalVelocity * 0.5) * -1;
				m_Transform->Y = m_OldY;
				m_Destination.Y = m_OldY;
			}
			else
			{
				m_Transform->Y = m_OldY;
				m_Destination.Y = m_OldY;
				m_VerticalVelocity = 0;
				if (m_CurrentState == Parachuting)
				{
					m_CurrentState = Flapping;
				}
			}
		}

		m_Destination.X = static_cast<int>(m_Transform->X);
		if (tLayer->IsColliding(m_Destination) != 0)
		{
			m_HorizontalVelocity = m_HorizontalVelocity * -1;


			m_Transform->X = m_OldX;
			m_Destination.X = m_OldX;
		}
	}

	SetVelocity();

	m_Transform->Translate(m_HorizontalVelocity * 0.05, m_VerticalVelocity * 0.05);

	if (m_Transform->X > 800)
	{
		m_Transform->X = 0;
	}
	else if (m_Transform->X < 0)
	{
		m_Transform->X = 800;
	}

	m_EnnemySprite->Update(m_Transform, aDeltaTime);
	m_OldX = m_Destination.X;
	m_OldY = m_Destination.Y;
}

void Ennemy::Start()
{
	m_EnnemySprite->Load(Assets::ENNEMY);
	m_Transform->SetPosition(static_cast<float>(m_Destination.X), static_cast<float>(m_Destination.Y));
	m_Transform->SetWidth(static_cast<float>(m_Destination.W));
	m_Transform->SetHeight(static_cast<float>(m_Destination.H));
	m_Transform->SetRotation(m_Angle);
	OiseauManager::Instance().AddOiseau(this);
	
}

void Ennemy::Destroy()
{
	m_EnnemySprite->Unload();
	SAFE_DELETE(m_EnnemySprite);
}

void Ennemy::GroundedUpdate(float aDeltaTime)
{
	if (m_FramesToTick < m_FrameCount)
	{
		//need to add animation of balloon pumping
		m_LiftoffCount++;
		if (m_LiftoffCount >= m_LiftoffTime)
		{
			m_LiftoffCount = 0;
			m_CurrentState = Flapping;
		}
		m_FrameCount = 0;
	}
	else
	{
		m_FrameCount++;
	}
}

void Ennemy::FlappingUpdate(float aDeltaTime)
{
	if (m_FramesToTick * 0.2 < m_FrameCount)
	{
		m_VerticalVelocity += m_JumpStrength;
		m_FrameCount = 0;

		if (m_Transform->Y < 70)
		{
			m_CurrentState = Falling;
		}

		if (m_SecondsToRotateTimer > m_SecondsToRotate)
		{
			m_Speed += m_Speed * -1;
			m_SecondsToRotateTimer = 0;
			std::cout << "TURNING" << std::endl;
		}
		else
		{
			m_SecondsToRotateTimer++;
		}
	}
	else
	{
		m_FrameCount++;
	}
}

void Ennemy::FallingUpdate(float aDeltaTime)
{
	if (m_FramesToTick < m_FrameCount)
	{
		if (m_TimeFalling < m_TimeFallingCount)
		{
			m_CurrentState = Flapping;
			m_TimeFallingCount = 0;
		}
		else
		{
			m_TimeFallingCount++;
		}

		if (m_SecondsToRotateTimer > m_SecondsToRotate)
		{
			m_Speed += m_Speed * -1;
			m_SecondsToRotateTimer = 0;
		}
		else
		{
			m_SecondsToRotateTimer++;
		}
		m_FrameCount = 0;
	}
	else
	{
		m_FrameCount++;
	}
}

void Ennemy::ParachutingUpdate(float aDeltaTime)
{
	if (m_FramesToTick < m_FrameCount)
	{
		m_Speed += m_Speed * -1;

		m_FrameCount = 0;
	}
	else
	{
		m_FrameCount++;
	}

}

void Ennemy::SetVelocity()
{
	if (m_VerticalVelocity > m_MinVerticalVelocity)
	{
		m_VerticalVelocity = m_MinVerticalVelocity;
	}
	else if (m_VerticalVelocity < m_MaxVerticalVelocity)
	{
		m_VerticalVelocity = m_MaxVerticalVelocity;
	}

	if (m_HorizontalVelocity > m_MinHorizontalVelocity)
	{
		m_HorizontalVelocity = m_MinHorizontalVelocity;
	}
	else if (m_HorizontalVelocity < m_MaxHorizontalVelocity)
	{
		m_HorizontalVelocity = m_MaxHorizontalVelocity;
	}
}

void Ennemy::SetRectangle(int aX, int aY, int aWidth, int aHeight, Color aColor, float aAngle)
{
	m_Destination.Set(aX, aY, aWidth, aHeight);
	m_Color.Set(aColor.R, aColor.G, aColor.B, aColor.A);
	m_Angle = aAngle;
	m_OldX = m_Destination.X;
	m_OldY = m_Destination.Y;
}

void EnnemyFactory::Create(const std::string& aName, const Rectangle& aDest, float aAngle, TiledProperties* aProps) const
{
	Ennemy* tEnnemy = new Ennemy();

	const Color tColor = aProps->GetColor("color");

	tEnnemy->SetRectangle(aDest.X, aDest.Y, aDest.W, aDest.H, tColor, aAngle);

	Engine::Instance().GetScene().AddEntity(aName, tEnnemy);
}