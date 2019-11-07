#include <Camera.h>
#include <Engine.h>

void bart::Camera::SetPosition(int aX, int aY)
{
    mViewport.X = aX;
    mViewport.Y = aY;
}

void bart::Camera::Move(int aX, int aY)
{
    mViewport.X += aX;
    mViewport.Y += aY;
}

void bart::Camera::SetViewport(int aX, int aY, int aWidth, int aHeight)
{
    mViewport.Set(aX, aY, aWidth, aHeight);
}

bool bart::Camera::CollideWith(const Rectangle& aRect)
{
    return Engine::Instance().GetCollision().IsColliding(mViewport, aRect);
}

bool bart::Camera::CollideWith(const Circle& aCircle)
{
    return Engine::Instance().GetCollision().IsColliding(mViewport, aCircle);
}

bool bart::Camera::CollideWidth(int aX, int aY)
{
    return Engine::Instance().GetCollision().IsColliding(mViewport, aX, aY);
}
