#include <Entity.h>
#include <Engine.h>

void bart::Entity::Update(float aDeltaTime)
{
}

void bart::Entity::Draw()
{
}

bart::IGraphic& bart::Entity::GetGraphics()
{
    return Engine::Instance().GetGraphic();
}

bart::ICollision& bart::Entity::GetCollision()
{
    return Engine::Instance().GetCollision();
}

bool bart::Entity::IsKeyDown(const EKeys aKey)
{
    return Engine::Instance().GetInput().IsKeyDown(aKey);
}

void bart::Entity::AddEntity(const std::string& aId, Entity* aEntity)
{
    return Engine::Instance().GetScene().AddEntity(aId, aEntity);
}

bart::Entity* bart::Entity::FindEntity(const std::string& aId)
{
    return Engine::Instance().GetScene().FindEntity(aId);
}

void bart::Entity::Load(const std::string& aId)
{
    return Engine::Instance().GetScene().Load(aId);
}
