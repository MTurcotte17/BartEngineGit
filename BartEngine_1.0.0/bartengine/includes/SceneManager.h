#ifndef BART_SCENE_MANAGER_H
#define BART_SCENE_MANAGER_H

#include <IScene.h>
#include <World.h>
#include <GameState.h>
#include <map>

namespace bart
{
    class SceneManager final : public IScene
    {
    public:
        virtual ~SceneManager() = default;

        bool Initialize() override;
        void Clean() override;

        void Register(const std::string& aId, GameState* aState) override;
        void Load(const std::string& aId) override;
        void Update(float aDeltaTime) override;
        void Draw() override;
        void AddEntity(const std::string& aId, Entity* aEntity) override;
        void Reset() override;

        Entity* FindEntity(const std::string& aId) override;

    private:
        typedef std::map<std::string, GameState*> TSceneMap;

        void LoadNextScene();

        World m_World;
        GameState* m_NextState{nullptr};
        std::string m_StateName;

        TSceneMap m_SceneMap;
    };
}

#endif
