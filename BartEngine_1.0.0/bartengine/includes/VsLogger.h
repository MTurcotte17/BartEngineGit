#ifndef BART_VS_LOGGER_H
#define BART_VS_LOGGER_H

#include <ILogger.h>

namespace bart
{
    class VsLogger final : public ILogger
    {
    public:
        virtual ~VsLogger() = default;

        bool Initialize() override;
        void Clean() override;

        void Log(const char* aMessage, ...) override;
    };
}
#endif
