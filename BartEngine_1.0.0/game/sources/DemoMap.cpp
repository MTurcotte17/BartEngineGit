#include <DemoMap.h>
#include <Engine.h>
#include "TileLayer.h"
#include <iostream>
#include "RectEntity.h"

DemoMap::DemoMap()
{
}

void DemoMap::Draw()
{
    m_Map.Draw();
}

void DemoMap::Update(float aDeltaTime)
{
    IInput& tInput = Engine::Instance().GetInput();

    if (tInput.IsKeyDown(KEY_LEFT))
    {
        m_Camera.Move(-4, 0);
    }
    else if (tInput.IsKeyDown(KEY_RIGHT))
    {
        m_Camera.Move(4, 0);
    }
}

void DemoMap::Start()
{
    m_Map.Register("Rect", new RectFactory());

    if (!m_Map.Load("Assets/Demo/demo.tmx"))
    {
        Engine::Instance().GetLogger().Log("Error loading map\n");
    }

    m_Camera.SetPosition(0, 0);
    m_Camera.SetViewport(0, 0, 800, 600);
    Engine::Instance().GetGraphic().SetCamera(&m_Camera);
}

void DemoMap::Destroy()
{
    m_Map.Clean();
}
