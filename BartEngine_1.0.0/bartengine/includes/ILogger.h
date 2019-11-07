#ifndef BART_ILOGGER_H
#define BART_ILOGGER_H

#include <IService.h>

namespace bart
{
    class ILogger : public IService
    {
    public:
        virtual ~ILogger() = default;
        virtual void Log(const char* aMessage, ...) = 0;
    };
}
#endif
