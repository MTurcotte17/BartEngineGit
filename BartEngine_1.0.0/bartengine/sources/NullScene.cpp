#include <NullScene.h>

bool bart::NullScene::Initialize()
{
    return true;
}

void bart::NullScene::Clean()
{
}

void bart::NullScene::Register(const std::string& aId, GameState* aState)
{
}

void bart::NullScene::Load(const std::string& aId)
{
}

void bart::NullScene::Update(float aDeltaTime)
{
}

void bart::NullScene::Draw()
{
}

void bart::NullScene::AddEntity(const std::string& aId, Entity* aEntity)
{
}

void bart::NullScene::Reset()
{
}

bart::Entity* bart::NullScene::FindEntity(const std::string& aId)
{
    return nullptr;
}
