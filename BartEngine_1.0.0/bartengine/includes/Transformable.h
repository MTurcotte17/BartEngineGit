#ifndef BART_TRANSFORMABLE_H
#define BART_TRANSFORMABLE_H

#include <Transform.h>

namespace bart
{
    class Transformable : public Component
    {
    public:
        virtual ~Transformable() = default;
        virtual void Update(Transform* aTransform, float aDelta) = 0;
    };
}

#endif
