#ifndef BART_NULL_TIMER_H
#define BART_NULL_TIMER_H

#include <ITimer.h>

namespace bart
{
    class NullTimer final : public ITimer
    {
    public:
        virtual ~NullTimer() = default;

        bool Initialize() override;
        void Clean() override;

        float GetTime() override;
        void Wait(float aTime) override;
    };
}

#endif
