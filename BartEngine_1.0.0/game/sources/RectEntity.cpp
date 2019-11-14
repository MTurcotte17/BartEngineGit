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
	//EX COL
	/*
	DemoMap* tEntity = static_cast<DemoMap*>(Engine::Instance().GetScene().FindEntity("DemoMap"));
	TileMap* tMap = tEntity->GetMap();
	TileLayer* tLayer = tMap->GetLayer<TileLayer>("Collision");

	
	m_Destination.Y = static_cast<int>(m_Transform->Y);

	if(tLayer != nullptr)
	{
		m_Destination.X = static_cast<int>(m_Transform->X);
		if(tLayer.IsCollising(m_Destination) != 0)
		{
			m_Transform.X = m_OldX;
			m_Destination.X = m_OldX;
		}

		m_Destination.Y = static_cast<int>(m_Transform->Y);
		if(tLayer.IsCollising(m_Destination) != 0)
		{
			m_Transform.Y = m_OldY;
			m_Destination.Y = m_OldY;
		}
	}


	*/
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
