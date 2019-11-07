#ifndef BART_RECTCOLLIDER_H
#define BART_RECTCOLLIDER_H

#include <Engine.h>
#include <Transformable.h>

namespace bart
{
    class RectCollider final : public Transformable
    {
    public:
        virtual ~RectCollider() = default;

        void Update(Transform* aTransform, float aDelta) override;

        bool IsColliding(const Rectangle& aRect) const;
        bool IsColliding(const Circle& aCircle) const;
        bool IsColliding(int aX, int aY) const;

        Rectangle GetRect() const { return m_Rect; }

    private:
        Rectangle m_Rect;
    };
}

#endif
