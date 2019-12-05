#include <Player.h>
#include <Engine.h>
#include <LevelOneMap.h>
#include <TileMap.h>
#include <TileLayer.h>
#include <Transform.h>
#include <Sprite.h>
#include <Assets.h>
#include <iostream>>
#include <LevelTwoMap.h>




Player::Player()
{
	m_Transform = new Transform;
	//m_PlayerSprite = new Sprite;
	m_Animator = new Animation;
}

void Player::Draw()
{
	if (!m_isDead)
	{
		if (m_isInvincible)
		{
			if (m_isDrawnDamaged)
			{
				m_isDrawnDamaged = false;
			}
			else if (!m_isDrawnDamaged)
			{
				m_Animator->Draw();
				m_isDrawnDamaged = true;
			}
		}
		else
		{
			m_Animator->Draw();
		}
	}
	//Engine::Instance().GetGraphic().SetColor(m_Color.R, m_Color.G, m_Color.B, m_Color.A);
	//Engine::Instance().GetGraphic().Fill(m_Destination);
}

void Player::Update(float aDeltaTime)
{
	IInput& tInput = Engine::Instance().GetInput();

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

	if (tInput.IsKeyDown(KEY_SPACE) && m_CanJump && m_Transform->Y > 0)
	{
		if (m_Lives == 2)
		{
			m_Animator->Play(7, 3, 0.1, false);
		}
		else
		{
			m_Animator->Play(17, 3, 0.1, false);
		}

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
		m_Transform->HorizontalFlipped = true;
	}

	if (tInput.IsKeyDown(KEY_D))
	{
		m_HorizontalVelocity += m_Speed;
		m_Transform->HorizontalFlipped = false;
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

	if (m_isInvincible)
	{
		if (m_InvincibleTimer > m_InvincibleDelay)
		{
			m_isInvincible = false;
			m_InvincibleTimer = 0;
		}
		else
		{
			m_InvincibleTimer++;
		}
	}
	if (m_isDead)
	{
		if (m_ReturnToMenuTimer > m_ReturnToMenuDelay)
		{
			OiseauManager::Instance().ClearList();
			bart::Engine::Instance().GetScene().Load("MainMenu");

		}
		else
		{
			m_ReturnToMenuTimer++;
		}
	}

	if (m_isVictory)
	{
		if (m_NextLevelTimer > m_NextLevelDelay)
		{
			m_isVictory = false;
			m_NextLevelTimer = 0;
			OiseauManager::Instance().ChangeLevel();
		}
		else
		{
			m_NextLevelTimer++;
		}
	}
	






	if (tDmgLayer != nullptr)
	{

		m_Destination.Y = static_cast<int>(m_Transform->Y);
		if (tDmgLayer->IsColliding(m_Destination) != 0)
		{
			m_isDead = true;
		}

		m_Destination.X = static_cast<int>(m_Transform->X);
		if (tLayer->IsColliding(m_Destination) != 0)
		{
			m_isDead = true;
		}
	}
	
	isColliding();

	if (!m_IsGrounded)
	{
		if (m_Lives == 2)
		{
			m_Animator->Play(7, 1, 0.2, true);
		}
		else if (m_Lives == 1) 
		{
			m_Animator->Play(17, 1, 0.2, true);
		}
	}

	m_VerticalVelocity += m_VelocityDecayRate;

	SetVelocity();

	m_Transform->Translate(m_HorizontalVelocity * 0.1, m_VerticalVelocity * 0.1);

	if (m_Transform->X > 800)
	{
		m_Transform->X = 0;
	}
	else if (m_Transform->X < 0)
	{
		m_Transform->X = 800;
	}

	if (m_IsGrounded && m_HorizontalVelocity == 0)
	{
		if (m_Lives == 2)
		{
			m_Animator->Play(0, 3, 0.2, true);
		}
		else
		{
			m_Animator->Play(10, 3, 0.2, true);
		}
	}
	else if (m_IsGrounded && m_HorizontalVelocity != 0)
	{
		if (m_Lives == 2)
		{
			m_Animator->Play(3, 3, 0.2, true);
		}
		else if (m_Lives == 1)
		{
			m_Animator->Play(13, 3, 0.2, true);
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

	m_Animator->Update(m_Transform, aDeltaTime);
	m_OldX = m_Destination.X;
	m_OldY = m_Destination.Y;
}



void Player::Start()
{
	m_Animator->InitAnimation(10, 16, 24);
	m_Animator->Load(Assets::PLAYER);
	m_Transform->SetPosition(static_cast<float>(m_Destination.X), static_cast<float>(m_Destination.Y));
	m_Transform->SetWidth(static_cast<float>(m_Destination.W));
	m_Transform->SetHeight(static_cast<float>(m_Destination.H));
	m_Transform->SetRotation(m_Angle);
	m_OiseauList = OiseauManager::Instance().GetOiseau();
	std::cout << m_OiseauList.size() << " size of ennemy list" << std::endl;
}

void Player::Destroy()
{
	m_Animator->Unload();
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

void Player::isColliding()
{
	for (int i = 0; i < m_OiseauList.size(); i++)
	{
		if (m_OiseauList[i]->IsActive())
		{
			//std::cout << m_Destination.X << ", " << m_Destination.Y << " Player" << std::endl;
			Rectangle tTemp = m_OiseauList[i]->GetDestination();
			//std::cout << tTemp.X << ", " << tTemp.Y << " Ennemy" << std::endl;
			if (m_Collision.IsColliding(m_Destination, m_OiseauList[i]->GetDestination()))
			{
				//std::cout << "checking collision with ennemy" << std::endl;
				if (!isTakingDamage(i))
				{
					if (!isDealingDamage(i))
					{
						std::cout << "Not Dealing Shit" << std::endl;
						m_HorizontalVelocity += (m_HorizontalVelocity * -1) * 2 ;
					}
				}
			}
		}
	}
}

bool Player::isTakingDamage(int aOiseauIndex)
{

	Rectangle tEnnemyDest = m_OiseauList[aOiseauIndex]->GetDestination();
	if (m_Destination.Y > tEnnemyDest.Y + tEnnemyDest.H * 0.75)
	{
		if (!m_isInvincible)
		{
			m_Lives--;
			if (m_Lives == 0)
			{
				
				m_isDead = true;
			}
			else
			{
				m_isInvincible = true;
			}
			m_VerticalVelocity = m_VerticalVelocity * -1;
		}
		return true;
	}
	return false;
}

bool Player::isDealingDamage(int aOiseauIndex)
{
	Rectangle tEnnemyDest = m_OiseauList[aOiseauIndex]->GetDestination();
	if (m_Destination.Y < tEnnemyDest.Y - tEnnemyDest.H * 0.75)
	{
		m_OiseauList[aOiseauIndex]->TakeDamage();
		m_VerticalVelocity = m_VerticalVelocity * -1;
		m_isVictory = OiseauManager::Instance().GetVictory();
		return true;
	}
	return false;
}

void PlayerFactory::Create(const std::string& aName, const Rectangle& aDest, float aAngle, TiledProperties* aProps) const
{
	Player* tPlayer = new Player();

	const Color tColor = aProps->GetColor("color");

	tPlayer->SetRectangle(aDest.X, aDest.Y, aDest.W, aDest.H, tColor, aAngle);

	Engine::Instance().GetScene().AddEntity(aName, tPlayer);
}
