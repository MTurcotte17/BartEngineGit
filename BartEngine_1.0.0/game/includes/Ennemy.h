#ifndef ENNEMY_H
#define ENNEMY_H

#include <Entity.h>
#include <Rectangle.h>
#include <ObjectFactory.h>
#include <Transform.h>
#include <Sprite.h>
#include <Animation.h>

using namespace bart;

class Ennemy final : public Entity
{
public:
	virtual ~Ennemy() = default;
	Ennemy();

	bool CanDraw() override { return true; }
	bool CanUpdate() override { return true; }

	void Draw() override;
	void Update(float aDeltaTime) override;
	void Start() override;
	void Destroy() override;

	void TakeDamage();



	void SetVelocity();

	void GroundedUpdate(float aDeltaTime);
	void FlappingUpdate(float aDeltaTime);
	void FallingUpdate(float aDeltaTime);
	void ParachutingUpdate(float aDeltaTime);
	void IdleUpdate(float aDeltaTime);

	Rectangle GetDestination() { return m_Destination; }



	void SetRectangle(int aX, int aY, int aWidth, int aHeight, Color aColor, float aAngle);

private:
	Rectangle m_Destination;
	Transform* m_Transform;
	Animation* m_Animator;
	Color m_Color;
	int m_OldX;
	int m_OldY;
	float m_Angle;

	int m_VerticalVelocity;
	int m_Speed = 3;
	int m_HorizontalVelocity;
	const int m_VelocityDecayRate = 1;
	const int m_JumpStrength = -15;
	const int m_MinHorizontalVelocity = 30;
	const int m_MaxHorizontalVelocity = -30;
	const int m_MinVerticalVelocity = 20;
	const int m_MaxVerticalVelocity = -50;

	bool m_isImmune = false;
	int m_ImmuneTimer = 0;
	int m_ImmuneDelay = 30;

	bool m_isFlickering = false;

	//counts seconds with game frames.
	int m_FramesToTick = 60;
	int m_FrameCount = 0;
	int m_SecondsToRotate = 15;
	int m_SecondsToRotateTimer = 0;

	int m_TimeFalling = 4;
	int m_TimeFallingCount = 0;


	//in seconds, time until the bird goes from grounded to flapping.
	int m_LiftoffTime = 3;
	int m_LiftoffCount = 0;

	//







	enum State
	{
		Grounded,
		Flapping,
		Falling,
		Parachuting,
		Idle
	};
	State m_CurrentState = Grounded;

};

class EnnemyFactory final : public BaseFactory
{
public:
	void Create(const std::string& aName, const Rectangle& aDest, float aAngle, TiledProperties* aProps) const override;
};




#endif