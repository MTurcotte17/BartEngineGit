#include <SdlTimer.h>
#include <SDL.h>

bool bart::SdlTimer::Initialize()
{
    return true;
}

void bart::SdlTimer::Clean()
{
}

float bart::SdlTimer::GetTime()
{
    return static_cast<float>(SDL_GetTicks());
}

void bart::SdlTimer::Wait(const float aTime)
{
    if (aTime > 0)
    {
        SDL_Delay(static_cast<Uint32>(aTime));
    }
}
