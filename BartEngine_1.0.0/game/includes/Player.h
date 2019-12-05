#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include <Rectangle.h>
#include <ObjectFactory.h>
#include <Transform.h>
#include <Sprite.h>
#include <BaseCollision.h>
#include <Ennemy.h>
#include <vector>
#include <iostream>
#include <OiseauManager.h>
#include <Animation.h>

using namespace bart;

class Player final : public Entity
{
public:
	virtual ~Player() = default;
	Player();

	bool CanDraw() override { return true; }
	bool CanUpdate() override { return true; }

	void Draw() override;
	void Update(float aDeltaTime) override;
	void Start() override;
	void Destroy() override;

	void SetVelocity();

	void SetRectangle(int aX, int aY, int aWidth, int aHeight, Color aColor, float aAngle);
	Rectangle& GetDestination() { return m_Destination; }

	void isColliding();

	bool isTakingDamage(int aOiseauIndex);
	bool isDealingDamage(int aOiseauIndex);

	



private:
	Rectangle m_Destination;
	Transform* m_Transform;
	Animation* m_Animator;

	int m_OldX;
	int m_OldY;
	float m_Angle;
	Color m_Color;
	//Sprite *m_PlayerSprite;
	int m_VerticalVelocity;
	int m_Speed = 1;
	int m_HorizontalVelocity;
	const int m_MinHorizontalVelocity = 30;
	const int m_MaxHorizontalVelocity = -30;
	const int m_MinVerticalVelocity = 50;
	const int m_MaxVerticalVelocity = -50;
	const int m_VelocityDecayRate = 1;
	const int m_JumpStrength = -15;
	bool m_IsGrounded = false;
	bool m_CanJump = true;
	bool m_isInvincible = false;
	int m_InvincibleTimer = 0;
	int m_InvincibleDelay = 120;
	bool m_isDrawnDamaged = true;
	bool m_isDead = false;
	int m_ReturnToMenuTimer = 0;
	int m_ReturnToMenuDelay = 120;
	bool m_isVictory = false;
	int m_NextLevelTimer = 0;
	int m_NextLevelDelay = 120;
	BaseCollision m_Collision;
	int m_Lives = 2;

	std::vector<Ennemy*> m_OiseauList;

	//int m_ReserveVelocity;

};

class PlayerFactory final : public BaseFactory
{
public:
	void Create(const std::string& aName, const Rectangle& aDest, float aAngle, TiledProperties* aProps) const override;
};
#endif