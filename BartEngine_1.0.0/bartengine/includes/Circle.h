#ifndef BART_CIRCLE_H
#define BART_CIRCLE_H

namespace bart
{
    class Circle
    {
    public:
        Circle(int aX, int aY, float aRadius)
        {
            X = aX;
            Y = aY;
            R = aRadius;
        }

        Circle()
        {
            X = 0;
            Y = 0;
            R = 0;
        }

        void Set(int aX, int aY, float aRadius);
        void Get(int* aX, int* aY, float* aRadius) const;

        int X{0};
        int Y{0};
        float R{0.0f};
    };
}

#endif
