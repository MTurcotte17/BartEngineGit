#include <ObjectFactory.h>

void bart::ObjectFactory::Register(const std::string& aType, BaseFactory* aFactory)
{
    if (m_Fatories.count(aType) == 0)
    {
        m_Fatories[aType] = aFactory;
    }
}

void bart::ObjectFactory::Create(const std::string& aType,
                                 const std::string& aName,
                                 const Rectangle& aDest,
                                 const float aAngle,
                                 TiledProperties* aProps)
{
    if (m_Fatories.count(aType) > 0)
    {
        m_Fatories[aType]->Create(aName, aDest, aAngle, aProps);
    }
}

void bart::ObjectFactory::Clear()
{
    for (std::map<std::string, BaseFactory*>::iterator tItr = m_Fatories.begin(); tItr != m_Fatories.end(); ++tItr)
    {
        delete tItr->second;
    }

    m_Fatories.clear();
}
