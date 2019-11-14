#include <CircleCollider.h>
#include <MathHelper.h>

void bart::CircleCollider::Update(Transform* aTransform, float /*aDelta*/)
{
    if (aTransform != nullptr)
    {
        const float tHalfW = aTransform->Width / 2;
        const float tHalfH = aTransform->Height / 2;
        const int tX = static_cast<int>(aTransform->X + tHalfW);
        const int tY = static_cast<int>(aTransform->Y + tHalfH);
        const float tRadius = MathHelper::Min(tHalfW, tHalfH);

        m_Circle.Set(tX, tY, tRadius);
    }
}

bool bart::CircleCollider::IsColliding(const Rectangle& aRect) const
{
    return Engine::Instance().GetCollision().IsColliding(aRect, m_Circle);
}

bool bart::CircleCollider::IsColliding(const Circle& aCircle) const
{
    return Engine::Instance().GetCollision().IsColliding(aCircle, m_Circle);
}

bool bart::CircleCollider::IsColliding(const int aX, const int aY) const
{
    return Engine::Instance().GetCollision().IsColliding(m_Circle, aX, aY);
}
