#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include <Rectangle.h>
#include <ObjectFactory.h>
#include <Transform.h>
#include <Sprite.h>

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

	void SetVerticalVelocity(int aVelo);

	void SetRectangle(int aX, int aY, int aWidth, int aHeight, Color aColor, float aAngle);
	Rectangle& GetDestination() { return m_Destination; }

private:
	Rectangle m_Destination;
	Transform* m_Transform;
	int m_OldX;
	int m_OldY;
	float m_Angle;
	Color m_Color;
	Sprite *m_PlayerSprite;
	int m_VerticalVelocity;
	const int m_MinVerticalVelocity = 2;
	const int m_MaxVerticalVelocity = -5;
	const int m_VelocityDecayRate = 4;
	const int m_JumpStrength = -20;
	int m_ReserveVelocity;

};

class PlayerFactory final : public BaseFactory
{
public:
	void Create(const std::string& aName, const Rectangle& aDest, float aAngle, TiledProperties* aProps) const override;
};
#endif