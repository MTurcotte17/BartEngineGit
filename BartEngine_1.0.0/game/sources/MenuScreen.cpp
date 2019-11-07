#include <MenuScreen.h>
#include "Assets.h"

MenuScreen::MenuScreen()
{
    m_MenuImage = new Sprite();
    m_Transform = new Transform();
	m_MenuBalloon = new Sprite();
	m_BalloonTransform = new Transform();
}

void MenuScreen::Start()
{
    IGraphic& tGraphic = GetGraphics();
    m_MenuImage->Load(Assets::BALLOON_TITLE);

    m_Transform->Width = 800;
    m_Transform->Height = 600;

    m_MenuImage->Update(m_Transform, 0.0f);

	m_MenuBalloon->Load(Assets::BALLOON_SELECT);
	m_BalloonTransform->Height = 55;
	m_BalloonTransform->Width = 38;
	m_BalloonTransform->X = 220.0f;
	m_BalloonTransform->Y = 390.0f;
	m_MenuBalloon->Update(m_BalloonTransform, 0.0f);


    tGraphic.SetCamera(&m_Camera);
}

void MenuScreen::Draw()
{
    IGraphic& tGraphic = GetGraphics();
    m_MenuImage->Draw();
	m_MenuBalloon->Draw();
}

void MenuScreen::Update(float aDeltaTime)
{
    static int tX = 0;
    static int tY = 0;

    if (Engine::Instance().GetInput().IsKeyDown(EKeys::KEY_LEFT))
    {
        tX -= 1;
    }
    else if (Engine::Instance().GetInput().IsKeyDown(EKeys::KEY_RIGHT))
    {
        tX += 1;
    }
	if (Engine::Instance().GetInput().IsKeyDown(EKeys::KEY_W))
	{
		
		if (!m_isOnePlayer)
		{
			m_isOnePlayer = true;
			m_BalloonTransform->Y = 390.0f;
			m_MenuBalloon->Update(m_BalloonTransform, 0.0f);
		}
	}
	else if (Engine::Instance().GetInput().IsKeyDown(EKeys::KEY_S))
	{
		if (m_isOnePlayer)
		{
			m_isOnePlayer = false;
			m_BalloonTransform->Y = 440.0f;
			m_MenuBalloon->Update(m_BalloonTransform, 0.0f);
		}
	}

    m_Camera.SetPosition(tX, tY);
}

void MenuScreen::Destroy()
{
    IGraphic& tGraphic = GetGraphics();

    tGraphic.SetCamera(nullptr);
    m_MenuImage->Unload();
	m_MenuBalloon->Unload();

    SAFE_DELETE(m_MenuImage);
    SAFE_DELETE(m_Transform);
	SAFE_DELETE(m_MenuBalloon);
	SAFE_DELETE(m_BalloonTransform);
}
