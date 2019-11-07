#ifndef BART_MATH_HELPER_H
#define BART_MATH_HELPER_H
#include <cstdlib>

namespace bart
{
    class MathHelper
    {
    public:

        static void SetSeed(int aSeed)
        {
            srand(aSeed);
        }

        static int RandomRange(const int aMin, const int aMax)
        {
            return aMin + (std::rand() % (aMax - aMin + 1));
        }

        template <class T>
        static T Clamp(const T aValue, const T aMin, const T aMax)
        {
            T tValue = aValue;

            if (tValue < aMin)
            {
                tValue = aMin;
            }
            else if (tValue > aMax)
            {
                tValue = aMax;
            }

            return tValue;
        }

        template <class T>
        static T Min(const T aValA, const T aValB)
        {
            if (aValB < aValA)
            {
                return aValB;
            }

            return aValA;
        }

        template <class T>
        static T Max(const T aValA, const T aValB)
        {
            if (aValB > aValA)
            {
                return aValB;
            }

            return aValA;
        }

        template <class T>
        static T Rotation(const T aValue, const T aMin, const T aMax)
        {
            if (aValue > aMax)
            {
                return aMin;
            }

            if (aValue < aMin)
            {
                return aMax;
            }

            return aValue;
        }
    };
}

#endif
