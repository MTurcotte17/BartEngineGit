#include <NullLogger.h>

bool bart::NullLogger::Initialize()
{
    return true;
}

void bart::NullLogger::Clean()
{
}

void bart::NullLogger::Log(const char* /*aMessage*/, ...)
{
}
