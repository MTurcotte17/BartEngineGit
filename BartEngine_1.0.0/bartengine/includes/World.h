#ifndef BART_WORLD_H
#define BART_WORLD_H

#include <string>
#include <map>
#include <vector>

namespace bart
{
    class Entity;

    class World
    {
    public:
        void Add(const std::string& aName, Entity* aEntity);
        Entity* FindByName(const std::string& aName);

        void StartEntities();

        void Unload();
        void Clean();

        void Update(float aDeltaTime);
        void Draw();

    private:
        typedef std::map<std::string, Entity*> TEntitiesMap;
        typedef std::vector<Entity*> TEntityVector;

        TEntitiesMap m_Entities;
        TEntityVector m_StartEntities;
        TEntityVector m_DrawEntities;
        TEntityVector m_UpdateEntities;
    };
}

#endif
