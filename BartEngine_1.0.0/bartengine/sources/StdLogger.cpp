#include <StdLogger.h>
#include <stdio.h>
#include <cstdarg>
#include <iostream>

bool bart::StdLogger::Initialize()
{
    return true;
}

void bart::StdLogger::Clean()
{
}

void bart::StdLogger::Log(const char* aMessage, ...)
{
    char tMessageBuffer[2048];
    va_list tArgs;
    va_start(tArgs, aMessage);
    const int tRetVal = vsprintf_s(tMessageBuffer, aMessage, tArgs);
    va_end(tArgs);
    tMessageBuffer[tRetVal] = '\0';

    std::cout << tMessageBuffer << std::endl;
}
