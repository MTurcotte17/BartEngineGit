#include <Player.h>
#include <Engine.h>
#include <LevelOneMap.h>
#include <TileMap.h>
#include <TileLayer.h>
#include <Transform.h>
#include <Sprite.h>
#include <Assets.h>
#include <iostream>




Player::Player()
{
	m_Transform = new Transform;
	m_PlayerSprite = new Sprite;
}

void Player::Draw()
{
	m_PlayerSprite->Draw();
	//Engine::Instance().GetGraphic().SetColor(m_Color.R, m_Color.G, m_Color.B, m_Color.A);
	//Engine::Instance().GetGraphic().Fill(m_Destination);
}

void Player::Update(float aDeltaTime)
{
	IInput& tInput = Engine::Instance().GetInput();

	LevelOneMap* tEntity = static_cast<LevelOneMap*>(Engine::Instance().GetScene().FindEntity("LevelOne"));
	TileMap* tMap = tEntity->GetMap();
	TileLayer* tLayer = tMap->GetLayer<TileLayer>("Collision");

	if (tInput.IsKeyDown(KEY_SPACE) && m_CanJump)
	{
		m_VerticalVelocity += m_JumpStrength;
		m_CanJump = false;
		m_IsGrounded = false;
	}
	else if (tInput.IsKeyUp(KEY_SPACE) && !m_CanJump)
	{
		m_CanJump = true;
	}

	if (tInput.IsKeyDown(KEY_A))
	{
		m_HorizontalVelocity -= m_Speed;
	}

	if (tInput.IsKeyDown(KEY_D))
	{
		m_HorizontalVelocity += m_Speed;
	}

	if (!tInput.IsKeyDown(KEY_D) && !tInput.IsKeyDown(KEY_A))
	{
		if (m_HorizontalVelocity > 0)
		{
			m_HorizontalVelocity -= m_Speed;
		}
		else if (m_HorizontalVelocity < 0)
		{
			m_HorizontalVelocity += m_Speed;
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
				m_IsGrounded = true;
				std::cout << "grounded" << std::endl;
			}
		}

		m_Destination.X = static_cast<int>(m_Transform->X);
		if (tLayer->IsColliding(m_Destination) != 0)
		{
			//if (m_OldX > m_Destination.X)
			//{
			if (!m_IsGrounded)
			{
				m_HorizontalVelocity = m_HorizontalVelocity * -1;
			}
			//}

			//else if(m_OldX)

			m_Transform->X = m_OldX;
			m_Destination.X = m_OldX;
		}
	}

//	if (!m_IsGrounded)
	//{
		m_VerticalVelocity += m_VelocityDecayRate;
	//}
	SetVelocity();

	std::cout << m_HorizontalVelocity << std::endl;
	m_Transform->Translate(m_HorizontalVelocity * 0.1, m_VerticalVelocity * 0.1);

	if (m_Transform->X > 800)
	{
		m_Transform->X = 0;
	}
	else if (m_Transform->X < 0)
	{
		m_Transform->X = 800;
	}
	
	m_PlayerSprite->Update(m_Transform, aDeltaTime);
	m_OldX = m_Destination.X;
	m_OldY = m_Destination.Y;
}



void Player::Start()
{
	m_PlayerSprite->Load(Assets::PLAYER);
	m_Transform->SetPosition(static_cast<float>(m_Destination.X), static_cast<float>(m_Destination.Y));
	m_Transform->SetWidth(static_cast<float>(m_Destination.W));
	m_Transform->SetHeight(static_cast<float>(m_Destination.H));
	m_Transform->SetRotation(m_Angle);
}

void Player::Destroy()
{
	m_PlayerSprite->Unload();
	SAFE_DELETE(m_Transform);
}

void Player::SetVelocity()
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

void Player::SetRectangle(int aX, int aY, int aWidth, int aHeight, Color aColor, float aAngle)
{
	m_Destination.Set(aX, aY, aWidth, aHeight);
	m_Color.Set(aColor.R, aColor.G, aColor.B, aColor.A);
	m_Angle = aAngle;
	m_OldX = m_Destination.X;
	m_OldY = m_Destination.Y;
}

void PlayerFactory::Create(const std::string& aName, const Rectangle& aDest, float aAngle, TiledProperties* aProps) const
{
	Player* tPlayer = new Player();

	const Color tColor = aProps->GetColor("color");

	tPlayer->SetRectangle(aDest.X, aDest.Y, aDest.W, aDest.H, tColor, aAngle);

	Engine::Instance().GetScene().AddEntity(aName, tPlayer);
}
