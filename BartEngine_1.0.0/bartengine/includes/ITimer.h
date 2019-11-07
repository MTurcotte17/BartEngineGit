#ifndef BART_ITIMER_H
#define BART_ITIMER_H

#include <IService.h>

namespace bart
{
    class ITimer : public IService
    {
    public:
        virtual ~ITimer() = default;

        virtual float GetTime() = 0;
        virtual void Wait(float aDelay) = 0;
    };
}

#endif
