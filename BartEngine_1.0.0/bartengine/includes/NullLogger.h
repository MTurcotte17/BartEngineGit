#ifndef BART_NULL_LOGGER_H
#define BART_NULL_LOGGER_H

#include <ILogger.h>

namespace bart
{
    class NullLogger final : public ILogger
    {
    public:
        virtual ~NullLogger() = default;

        bool Initialize() override;
        void Clean() override;

        void Log(const char* aMessage, ...) override;
    };
}
#endif
