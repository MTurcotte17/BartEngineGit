#include <LevelTwoMap.h>
#include <Engine.h>
#include <TileLayer.h>
#include <iostream>
#include <Player.h>
#include <Ennemy.h>
#include <OiseauManager.h>


LevelTwoMap::LevelTwoMap()
{
}

void LevelTwoMap::Draw()
{
	m_Map.Draw();
}

void LevelTwoMap::Update(float aDeltaTime)
{

}

void LevelTwoMap::Start()
{

	m_Map.Register("Ennemy", new EnnemyFactory());
	m_Map.Register("Player", new PlayerFactory());

	if (!m_Map.Load("Assets/Demo/Level2.tmx"))
	{
		Engine::Instance().GetLogger().Log("Error loading map\n");
	}

	m_Camera.SetPosition(0, 0);
	m_Camera.SetViewport(0, 0, 800, 600);
	Engine::Instance().GetGraphic().SetCamera(&m_Camera);

}

void LevelTwoMap::Destroy()
{
	m_Map.Clean();
}
