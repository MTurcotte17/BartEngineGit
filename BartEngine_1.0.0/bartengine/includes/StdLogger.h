#ifndef BART_STD_LOGGER_H
#define BART_STD_LOGGER_H

#include <ILogger.h>

namespace bart
{
    class StdLogger final : public ILogger
    {
    public:
        virtual ~StdLogger() = default;

        bool Initialize() override;
        void Clean() override;

        void Log(const char* aMessage, ...) override;
    };
}
#endif
