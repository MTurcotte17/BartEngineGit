#ifndef BART_CAMERA_H
#define BART_CAMERA_H

#include <Rectangle.h>
#include <Circle.h>
#include <Component.h>

namespace bart
{
    class Camera : public Component
    {
    public:
        Camera() = default;
        virtual ~Camera() = default;

        void SetPosition(int aX, int aY);
        void Move(int aX, int aY);
        void SetViewport(int aX, int aY, int aWidth, int aHeight);

        int GetX() const { return mViewport.X; }
        int GetY() const { return mViewport.Y; }
        int GetWidth() const { return mViewport.W; }
        int GetHeight() const { return mViewport.H; }

        bool CollideWith(const Rectangle& aRect);
        bool CollideWith(const Circle& aCircle);
        bool CollideWidth(int aX, int aY);
        Rectangle& GetViewport() { return mViewport; }

    private:
        Rectangle mViewport;
    };
}

#endif
