#ifndef BART_TRANSFORM_H
#define BART_TRANSFORM_H

#include <Component.h>

namespace bart
{
    class Transform final : public Component
    {
    public:
        virtual ~Transform() = default;

        void SetPosition(float aX, float aY);
        void Translate(float aX, float aY);
        void SetRotation(float aAngle);
        void Rotate(float aAngle);
        void SetWidth(float aWidth);
        void SetHeight(float aHeight);
        void SetFlip(bool aHorizontal, bool aVertical);

        float X{0.0f};
        float Y{0.0f};
        float Angle{0.0f};
        float Width{100.0f};
        float Height{100.0f};
        bool HorizontalFlipped{false};
        bool VerticalFlipped{false};
    };
}

#endif
