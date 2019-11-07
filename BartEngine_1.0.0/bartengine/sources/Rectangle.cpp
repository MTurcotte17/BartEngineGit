#include <Rectangle.h>

void bart::Rectangle::Set(const int aX, const int aY, const int aWidth, const int aHeight)
{
    X = aX;
    Y = aY;
    W = aWidth;
    H = aHeight;
}

void bart::Rectangle::Get(int* aX, int* aY, int* aWidth, int* aHeight) const
{
    *aX = X;
    *aY = Y;
    *aWidth = W;
    *aHeight = H;
}
