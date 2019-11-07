#ifndef BART_ISERVICE_H
#define BART_ISERVICE_H

namespace bart
{
    class IService
    {
    public:
        virtual ~IService() = default;

        virtual bool Initialize() = 0;
        virtual void Clean() = 0;
    };
}

#endif
