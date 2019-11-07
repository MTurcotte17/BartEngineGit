#include <Point.h>

void bart::Point::Set(const int aX, const int aY)
{
    X = aX;
    Y = aY;
}

void bart::Point::Get(int* aX, int* aY) const
{
    *aX = X;
    *aY = Y;
}
