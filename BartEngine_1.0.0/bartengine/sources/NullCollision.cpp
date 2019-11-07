#include <NullCollision.h>

bool bart::NullCollision::Initialize()
{
    return true;
}

void bart::NullCollision::Clean()
{
}

bool bart::NullCollision::IsColliding(const Rectangle& aRectA, const Rectangle& aRectB)
{
    return false;
}

bool bart::NullCollision::IsColliding(const Rectangle& aRect, const Point& aPoint)
{
    return false;
}

bool bart::NullCollision::IsColliding(const Rectangle& aRect, int aX, int aY)
{
    return false;
}

bool bart::NullCollision::IsColliding(const Circle& aCircle, int aX, int aY)
{
    return false;
}

bool bart::NullCollision::IsColliding(const Circle& aCircle, const Point& aPoint)
{
    return false;
}

bool bart::NullCollision::IsColliding(const Circle& aCircleA, const Circle& aCircleB)
{
    return false;
}

bool bart::NullCollision::IsColliding(const Rectangle& aRect, const Circle& aCircle)
{
    return false;
}
