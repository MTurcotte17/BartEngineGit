#include <Circle.h>

void bart::Circle::Set(const int aX, const int aY, const float aRadius)
{
    X = aX;
    Y = aY;
    R = aRadius;
}

void bart::Circle::Get(int* aX, int* aY, float* aRadius) const
{
    *aX = X;
    *aY = Y;
    *aRadius = R;
}
