#ifndef BART_NULL_COLLISION_H
#define BART_NULL_COLLISION_H

#include <ICollision.h>

namespace bart
{
    class NullCollision final : public ICollision
    {
    public:
        virtual ~NullCollision() = default;

        bool Initialize() override;
        void Clean() override;

        bool IsColliding(const Rectangle& aRectA, const Rectangle& aRectB) override;
        bool IsColliding(const Rectangle& aRect, const Point& aPoint) override;
        bool IsColliding(const Rectangle& aRect, int aX, int aY) override;
        bool IsColliding(const Circle& aCircle, int aX, int aY) override;
        bool IsColliding(const Circle& aCircle, const Point& aPoint) override;
        bool IsColliding(const Circle& aCircleA, const Circle& aCircleB) override;
        bool IsColliding(const Rectangle& aRect, const Circle& aCircle) override;
    };
}

#endif
