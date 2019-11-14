#include <RectCollider.h>

void bart::RectCollider::Update(Transform* aTransform, float /*aDelta*/)
{
    if (aTransform != nullptr)
    {
        const int tX = static_cast<int>(aTransform->X);
        const int tY = static_cast<int>(aTransform->Y);
        const int tW = static_cast<int>(aTransform->Width);
        const int tH = static_cast<int>(aTransform->Height);

        m_Rect.Set(tX, tY, tW, tH);
    }
}

bool bart::RectCollider::IsColliding(const Rectangle& aRect) const
{
    return Engine::Instance().GetCollision().IsColliding(aRect, m_Rect);
}

bool bart::RectCollider::IsColliding(const Circle& aCircle) const
{
    return Engine::Instance().GetCollision().IsColliding(m_Rect, aCircle);
}

bool bart::RectCollider::IsColliding(const int aX, const int aY) const
{
    return Engine::Instance().GetCollision().IsColliding(m_Rect, aX, aY);
}
