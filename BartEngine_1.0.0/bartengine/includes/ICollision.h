#ifndef BART_ICOLLISION_H
#define BART_ICOLLISION_H

#include <IService.h>
#include <Point.h>
#include <Circle.h>

namespace bart
{
    class Rectangle;

    class ICollision : public IService
    {
    public:
        virtual ~ICollision() = default;

        virtual bool IsColliding(const Rectangle& aRectA, const Rectangle& aRectB) = 0;
        virtual bool IsColliding(const Rectangle& aRect, const Point& aPoint) = 0;
        virtual bool IsColliding(const Rectangle& aRect, int aX, int aY) = 0;
        virtual bool IsColliding(const Circle& aCircle, int aX, int aY) = 0;
        virtual bool IsColliding(const Circle& aCircle, const Point& aPoint) = 0;
        virtual bool IsColliding(const Circle& aCircleA, const Circle& aCircleB) = 0;
        virtual bool IsColliding(const Rectangle& aRect, const Circle& aCircle) = 0;
    };
}

#endif
