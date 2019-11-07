#include <VsLogger.h>
#include <stdio.h>
#include <cstdarg>
#include <Windows.h>

bool bart::VsLogger::Initialize()
{
    return true;
}

void bart::VsLogger::Clean()
{
}

void bart::VsLogger::Log(const char* aMessage, ...)
{
    char tMessageBuffer[2048];
    va_list tArgs;
    va_start(tArgs, aMessage);
    const int tRetVal = vsprintf_s(tMessageBuffer, aMessage, tArgs);
    va_end(tArgs);
    tMessageBuffer[tRetVal] = '\0';

    OutputDebugString(tMessageBuffer);
}
