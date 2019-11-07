#include <RectEntity.h>
#include "Engine.h"

RectEntity::RectEntity()
{

}

void RectEntity::Draw()
{   
    Engine::Instance().GetGraphic().SetColor(m_Color.R, m_Color.G, m_Color.B, 255);
    Engine::Instance().GetGraphic().Draw(m_Destination);
}

void RectEntity::Update(float aDeltaTime)
{

}

void RectEntity::Start()
{

}

void RectEntity::Destroy()
{

}

void RectEntity::SetRectangle(int aX, int aY, int aWidth, int aHeight, Color aColor, float aAngle)
{
    m_Destination.Set(aX, aY, aWidth, aHeight);
    m_Color.Set(aColor.R, aColor.G, aColor.B, aColor.A);
    m_Angle = aAngle;
}

void RectFactory::Create(const std::string& aName, const Rectangle& aDest, float aAngle, TiledProperties* aProps) const
{
    RectEntity* tRectEntity = new RectEntity();

    const Color tColor = aProps->GetColor("color");

    tRectEntity->SetRectangle(aDest.X, aDest.Y, aDest.W, aDest.H, tColor, aAngle);

    Engine::Instance().GetScene().AddEntity(aName, tRectEntity);
}
