#include <FileLogger.h>
#include <stdio.h>
#include <cstdarg>

bool bart::FileLogger::Initialize()
{
    m_File.open("engine.txt", std::ios::out);

    return m_File.is_open();
}

void bart::FileLogger::Clean()
{
    if (m_File.is_open())
    {
        m_File.close();
    }
}

void bart::FileLogger::Log(const char* aMessage, ...)
{
    char tMessageBuffer[2048];
    va_list tArgs;
    va_start(tArgs, aMessage);
    const int tRetVal = vsprintf_s(tMessageBuffer, aMessage, tArgs);
    va_end(tArgs);
    tMessageBuffer[tRetVal] = '\0';

    m_File << tMessageBuffer << std::endl;
}
