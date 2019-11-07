#ifndef BART_CIRCLECOLLIDER_H
#define BART_CIRCLECOLLIDER_H

#include <Engine.h>
#include <Transformable.h>

namespace bart
{
    class CircleCollider final : public Transformable
    {
    public:
        virtual ~CircleCollider() = default;

        void Update(Transform* aTransform, float aDelta) override;

        bool IsColliding(const Rectangle& aRect) const;
        bool IsColliding(const Circle& aCircle) const;
        bool IsColliding(int aX, int aY) const;

        Circle GetCircle() const { return m_Circle; }

    private:
        Circle m_Circle;
    };
}

#endif
