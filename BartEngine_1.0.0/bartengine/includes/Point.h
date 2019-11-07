#ifndef BART_POINT_H
#define BART_POINT_H

namespace bart
{
    class Point
    {
    public:
        void Set(int aX, int aY);
        void Get(int* aX, int* aY) const;

        int X{0};
        int Y{0};
    };
}

#endif
