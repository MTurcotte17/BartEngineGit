#include <SceneManager.h>
#include "Engine.h"

bool bart::SceneManager::Initialize()
{
    return true;
}

void bart::SceneManager::Clean()
{
    for (TSceneMap::iterator itr = m_SceneMap.begin(); itr != m_SceneMap.end(); ++itr)
    {
        delete itr->second;
    }

    m_SceneMap.clear();
    m_World.Clean();
}

void bart::SceneManager::Register(const std::string& aId, GameState* aState)
{
    if (m_SceneMap.count(aId) == 0)
    {
        m_SceneMap[aId] = aState;
    }
}

void bart::SceneManager::Load(const std::string& aId)
{
    if (m_SceneMap.count(aId) > 0)
    {
        m_StateName = aId;
        m_NextState = m_SceneMap[aId];
    }
}

void bart::SceneManager::Update(const float aDeltaTime)
{
    m_World.Update(aDeltaTime);

    m_World.StartEntities();

    LoadNextScene();
}

void bart::SceneManager::Draw()
{
    m_World.Draw();
}

void bart::SceneManager::AddEntity(const std::string& aId, Entity* aEntity)
{
    m_World.Add(aId, aEntity);
}

void bart::SceneManager::Reset()
{
    m_NextState = m_SceneMap[m_StateName];
}

bart::Entity* bart::SceneManager::FindEntity(const std::string& aId)
{
    return m_World.FindByName(aId);
}

void bart::SceneManager::LoadNextScene()
{
    if (m_NextState != nullptr)
    {
        m_World.Unload();
        m_NextState->Load();
        m_NextState = nullptr;
    }
}
