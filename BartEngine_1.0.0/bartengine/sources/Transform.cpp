#include <Transform.h>

void bart::Transform::SetPosition(const float aX, const float aY)
{
    X = aX;
    Y = aY;
}

void bart::Transform::Translate(const float aX, const float aY)
{
    X += aX;
    Y += aY;
}

void bart::Transform::SetRotation(const float aAngle)
{
    Angle = aAngle;

    while (Angle > 360.0f)
    {
        Angle = Angle - 360;
    }
}

void bart::Transform::Rotate(const float aAngle)
{
    Angle += aAngle;

    while (Angle > 360.0f)
    {
        Angle = Angle - 360;
    }
}

void bart::Transform::SetWidth(const float aWidth)
{
    Width = aWidth;
}

void bart::Transform::SetHeight(const float aHeight)
{
    Height = aHeight;
}

void bart::Transform::SetFlip(const bool aHorizontal, const bool aVertical)
{
    HorizontalFlipped = aHorizontal;
    VerticalFlipped = aVertical;
}
