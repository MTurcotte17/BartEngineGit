#include <World.h>
#include <Entity.h>
#include "Engine.h"

void bart::World::Add(const std::string& aName, Entity* aEntity)
{
    if (m_Entities.count(aName) == 0)
    {
        aEntity->SetName(aName);
        m_StartEntities.push_back(aEntity);
    }
}

bart::Entity* bart::World::FindByName(const std::string& aName)
{
    if (m_Entities.count(aName) > 0)
    {
        return m_Entities[aName];
    }
    return nullptr;
}

void bart::World::StartEntities()
{
    if (m_StartEntities.size() > 0)
    {
        std::vector<Entity*> tEntities = m_StartEntities;
        m_StartEntities.clear();

        for (size_t i = 0; i < tEntities.size(); i++)
        {
            Entity* tEntity = tEntities[i];

            m_Entities[tEntity->GetName()] = tEntity;

            if (tEntity->CanDraw())
            {
                m_DrawEntities.push_back(tEntity);
            }

            if (tEntity->CanUpdate())
            {
                m_UpdateEntities.push_back(tEntity);
            }
        }

        for (size_t i = 0; i < tEntities.size(); i++)
        {
            Entity* tEntity = tEntities[i];
            tEntity->Start();
        }

        tEntities.clear();
    }
}

void bart::World::Unload()
{
    for (TEntitiesMap::iterator itr = m_Entities.begin(); itr != m_Entities.end(); ++itr)
    {
        if (itr->second != nullptr)
        {
            itr->second->Destroy();
            delete itr->second;
        }
    }

    m_Entities.clear();
    m_DrawEntities.clear();
    m_UpdateEntities.clear();

#if DEBUG_CACHES
    const int tTextureCnt = Engine::Instance().GetGraphic().GetTextureInCache();
    if (tTextureCnt > 0)
    {
        Engine::Instance().GetLogger().Log("*** WARNING: %d texture(s) still in cache ***\n", tTextureCnt);
    }

    const int tFontCnt = Engine::Instance().GetGraphic().GetFontInCache();
    if (tFontCnt > 0)
    {
        Engine::Instance().GetLogger().Log("*** WARNING: %d font(s) still in cache ***\n", tFontCnt);
    }

    const int tSoundCnt = Engine::Instance().GetAudio().GetSoundInCache();
    if (tSoundCnt > 0)
    {
        Engine::Instance().GetLogger().Log("*** WARNING: %d sound(s) still in cache ***\n", tSoundCnt);
    }

    const int tMusicCnt = Engine::Instance().GetAudio().GetMusicInCache();
    if (tMusicCnt > 0)
    {
        Engine::Instance().GetLogger().Log("*** WARNING: %d music(s) still in cache ***\n", tMusicCnt);
    }
#endif
}

void bart::World::Clean()
{
    Unload();
}

void bart::World::Update(float aDeltaTime)
{
    for (TEntityVector::iterator itr = m_UpdateEntities.begin(); itr != m_UpdateEntities.end(); ++itr)
    {
        Entity* tEntity = *itr;

        if (tEntity != nullptr && tEntity->IsActive())
        {
            (*itr)->Update(aDeltaTime);
        }
    }
}

void bart::World::Draw()
{
    for (TEntityVector::iterator itr = m_DrawEntities.begin(); itr != m_DrawEntities.end(); ++itr)
    {
        Entity* tEntity = *itr;

        if (tEntity != nullptr && tEntity->IsActive())
        {
            (*itr)->Draw();
        }
    }
}
