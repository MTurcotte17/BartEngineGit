#ifndef BART_NULL_SCENE_H
#define BART_NULL_SCENE_H

#include <IScene.h>
#include <World.h>
#include <GameState.h>

namespace bart
{
    class NullScene final : public IScene
    {
    public:
        virtual ~NullScene() = default;

        bool Initialize() override;
        void Clean() override;

        void Register(const std::string& aId, GameState* aState) override;
        void Load(const std::string& aId) override;
        void Update(float aDeltaTime) override;
        void Draw() override;
        void AddEntity(const std::string& aId, Entity* aEntity) override;
        void Reset() override;

        Entity* FindEntity(const std::string& aId) override;
    };
}

#endif
