#include <LevelOneMap.h>
#include <Engine.h>
#include <TileLayer.h>
#include <iostream>
#include <Player.h>


LevelOneMap::LevelOneMap()
{
}

void LevelOneMap::Draw()
{
	m_Map.Draw();
}

void LevelOneMap::Update(float aDeltaTime)
{

}

void LevelOneMap::Start()
{
	m_Map.Register("Player", new PlayerFactory());

	if (!m_Map.Load("Assets/Demo/BalloonMenu.tmx"))
	{
		Engine::Instance().GetLogger().Log("Error loading map\n");
	}

	m_Camera.SetPosition(0, 0);
	m_Camera.SetViewport(0, 0, 800, 600);
	Engine::Instance().GetGraphic().SetCamera(&m_Camera);
}

void LevelOneMap::Destroy()
{
	m_Map.Clean();
}
