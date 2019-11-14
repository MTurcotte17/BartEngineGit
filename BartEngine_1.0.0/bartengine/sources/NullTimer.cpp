#include <NullTimer.h>

bool bart::NullTimer::Initialize()
{
    return true;
}

void bart::NullTimer::Clean()
{
}

float bart::NullTimer::GetTime()
{
    return 0.0f;
}

void bart::NullTimer::Wait(float /*aTime*/)
{
}
