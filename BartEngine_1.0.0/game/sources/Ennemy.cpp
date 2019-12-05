#include <Assets.h>
#include <Ennemy.h>
#include <TileMap.h>
#include <TileLayer.h>
#include <iostream>
#include <LevelOneMap.h>
#include <OiseauManager.h>
#include <LevelTwoMap.h>

Ennemy::Ennemy()
{
	m_Transform = new Transform;
	m_Animator = new Animation;
}

void Ennemy::Draw()
{
	if (m_isImmune)
	{
		if (m_isFlickering)
		{
			m_isFlickering = false;
		}
		else
		{
			m_isFlickering = true;
			m_Animator->Draw();
		}
	}
	else
	{
		m_Animator->Draw();
	}
}

void Ennemy::Update(float aDeltaTime)
{

	LevelOneMap* tEntity = static_cast<LevelOneMap*>(Engine::Instance().GetScene().FindEntity("LevelOne"));
	LevelTwoMap* tEntity2 = static_cast<LevelTwoMap*>(Engine::Instance().GetScene().FindEntity("LevelTwo"));
	TileMap* tMap;
	if (tEntity != nullptr)
	{
		tMap = tEntity->GetMap();
	}
	else
	{
		tMap = tEntity2->GetMap();
	}
	TileLayer* tLayer = tMap->GetLayer<TileLayer>("Collision");
	TileLayer* tDmgLayer = tMap->GetLayer<TileLayer>("Damage");

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
		case Idle:
		{
			IdleUpdate(aDeltaTime);
			break;
		}
	}

	if (m_CurrentState == Parachuting || m_CurrentState == Falling || m_CurrentState == Flapping)
	{
		m_HorizontalVelocity += m_Speed;
		m_VerticalVelocity += m_VelocityDecayRate;
	}

	if (m_isImmune)
	{
		if (m_ImmuneTimer > m_ImmuneDelay)
		{
			m_isImmune = false;
			m_ImmuneTimer = 0;
		}
		else
		{
			m_ImmuneTimer++;
		}
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
					m_CurrentState = Idle;
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

	if (tDmgLayer != nullptr)
	{

		m_Destination.Y = static_cast<int>(m_Transform->Y);
		if (tDmgLayer->IsColliding(m_Destination) != 0)
		{
			OiseauManager::Instance().RemoveOiseau();
			SetActive(false);
		}

		m_Destination.X = static_cast<int>(m_Transform->X);
		if (tLayer->IsColliding(m_Destination) != 0)
		{
			OiseauManager::Instance().RemoveOiseau();
			SetActive(false);
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

	m_Animator->Update(m_Transform, aDeltaTime);
	m_OldX = m_Destination.X;
	m_OldY = m_Destination.Y;
}

void Ennemy::Start()
{
	m_Animator->InitAnimation(12, 16, 24);
	m_Animator->Load(Assets::ENNEMY);
	m_Transform->SetPosition(static_cast<float>(m_Destination.X), static_cast<float>(m_Destination.Y));
	m_Transform->SetWidth(static_cast<float>(m_Destination.W));
	m_Transform->SetHeight(static_cast<float>(m_Destination.H));
	m_Transform->SetRotation(m_Angle);
	OiseauManager::Instance().AddOiseau(this);
	
}

void Ennemy::Destroy()
{
	OiseauManager::Instance().ClearList();
	m_Animator->Unload();
	SAFE_DELETE(m_Animator);
}

void Ennemy::TakeDamage()
{
	if (m_CurrentState == Flapping || m_CurrentState == Falling)
	{
		m_CurrentState = Parachuting;
		m_isImmune = true;
		std::cout << "Parachuting" << std::endl;
	}
	else
	{
		if (!m_isImmune)
		{
			OiseauManager::Instance().RemoveOiseau();
			SetActive(false);
		}
	}
}

void Ennemy::GroundedUpdate(float aDeltaTime)
{
	m_Animator->Play(5, 6, 0.5, false);
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
		m_Animator->Play(0, 3, 0.3, true);

		if (m_Transform->Y < 70)
		{
			m_CurrentState = Falling;
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
	//std::cout << "PARACHUTATION" << std::endl;
	m_Animator->Play(3, 1, 0.3, true);
	if (m_FramesToTick < m_FrameCount)
	{
		m_Speed += m_Speed * -1;
		m_VerticalVelocity = -2;
		m_FrameCount = 0;
	}
	else
	{
		m_FrameCount++;
	}

}

void Ennemy::IdleUpdate(float aDeltaTime)
{
	m_Animator->Play(11, 1, 1, true);
	m_VerticalVelocity = 0;
	m_HorizontalVelocity = 0;
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
