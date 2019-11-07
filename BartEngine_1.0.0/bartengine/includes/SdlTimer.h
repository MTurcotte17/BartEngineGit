#ifndef BART_SDL_TIMER_H
#define BART_SDL_TIMER_H

#include <ITimer.h>

namespace bart
{
    class SdlTimer final : public ITimer
    {
    public:
        virtual ~SdlTimer() = default;

        bool Initialize() override;
        void Clean() override;

        float GetTime() override;
        void Wait(float aTime) override;
    };
}

#endif
