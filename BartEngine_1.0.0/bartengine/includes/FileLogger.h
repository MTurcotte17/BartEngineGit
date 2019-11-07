#ifndef BART_FILE_LOGGER_H
#define BART_FILE_LOGGER_H

#include <ILogger.h>
#include <fstream>

namespace bart
{
    class FileLogger final : public ILogger
    {
    public:
        virtual ~FileLogger() = default;

        bool Initialize() override;
        void Clean() override;

        void Log(const char* aMessage, ...) override;

    private:
        std::fstream m_File;
    };
}
#endif
