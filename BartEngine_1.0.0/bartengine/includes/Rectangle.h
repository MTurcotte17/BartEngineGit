#ifndef BART_RECTANGLE_H
#define BART_RECTANGLE_H

namespace bart
{
    class Rectangle
    {
    public:
        void Set(int aX, int aY, int aWidth, int aHeight);
        void Get(int* aX, int* aY, int* aWidth, int* aHeight) const;

        int X{0};
        int Y{0};
        int W{0};
        int H{0};
    };
}

#endif
