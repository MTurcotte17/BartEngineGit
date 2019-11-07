#ifndef BART_OBJECT_FACTORY_H
#define BART_OBJECT_FACTORY_H

#include <string>
#include <Rectangle.h>
#include <TiledProperty.h>

namespace bart
{
    class BaseFactory
    {
    public:
        virtual ~BaseFactory() = default;

        virtual void Create(const std::string& aName,
                            const Rectangle& aDest,
                            float aAngle,
                            TiledProperties* aProps) const = 0;
    };

    class ObjectFactory
    {
    public:
        ObjectFactory() = default;
        ~ObjectFactory() = default;

        void Register(const std::string& aType, BaseFactory* aFactory);
        void Create(const std::string& aType,
                    const std::string& aName,
                    const Rectangle& aDest,
                    float aAngle,
                    TiledProperties* aProps);

        void Clear();

    private:
        std::map<std::string, BaseFactory*> m_Fatories;
    };
}

#endif
