#ifndef BART_ISCENE_H
#define BART_ISCENE_H

#include <IService.h>
#include <string>
#include <GameState.h>
#include <Entity.h>

namespace bart
{
    class IScene : public IService
    {
    public:
        virtual ~IScene() = default;

        virtual void Register(const std::string& aId, GameState* aState) = 0;
        virtual void Load(const std::string& aId) = 0;

        virtual void Update(float aDeltaTime) = 0;
        virtual void Draw() = 0;

        virtual void AddEntity(const std::string& aId, Entity* aEntity) = 0;
        virtual Entity* FindEntity(const std::string& aId) = 0;
        virtual void Reset() = 0;
    };
}

#endif
