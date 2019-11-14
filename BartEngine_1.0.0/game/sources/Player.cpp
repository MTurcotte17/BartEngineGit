#include <Player.h>
#include <Engine.h>
#include <LevelOneMap.h>
#include <TileMap.h>
#include <TileLayer.h>
#include <Transform.h>
#include <Sprite.h>
#include <Assets.h>



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

	if (tInput.IsKeyDown(KEY_SPACE))
	{
		SetVerticalVelocity(m_JumpStrength);
	}
	SetVerticalVelocity(m_VelocityDecayRate);



	m_Destination.Y = static_cast<int>(m_Transform->Y);
	if (tLayer != nullptr)
	{
		m_Destination.X = static_cast<int>(m_Transform->X);
		if (tLayer->IsColliding(m_Destination) != 0)
		{
			m_Transform->X = m_OldX;
			m_Destination.X = m_OldX;
		}

		m_Destination.Y = static_cast<int>(m_Transform->Y);
		if (tLayer->IsColliding(m_Destination) != 0)
		{
			m_Transform->Y = m_OldY;
			m_Destination.Y = m_OldY;
			m_VerticalVelocity = 0;
		}
	}

	m_Transform->Translate(0, m_VerticalVelocity);
	
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

void Player::SetVerticalVelocity(int aVelo)
{
	m_VerticalVelocity += aVelo;

	if (m_VerticalVelocity > m_MinVerticalVelocity)
	{
		m_VerticalVelocity = m_MinVerticalVelocity;
		m_ReserveVelocity = 0;
	}
	else if (m_VerticalVelocity < m_MaxVerticalVelocity)
	{
		m_ReserveVelocity = 
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
