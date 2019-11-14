#include <MenuOption.h>
#include <MenuScreen.h>
#include "Assets.h"

MenuOption::MenuOption()
{
    //m_MenuOption = new Text();
    //m_Transform = new Transform();
	m_OnePlayer = new Text();
	m_TwoPlayer = new Text();
	m_Text1Transform = new Transform();
	m_Text2Transform = new Transform();
	
}

void MenuOption::Start()
{
    IGraphic& tGraphic = GetGraphics();
   // m_MenuOption->Load(Assets::EIGHTBIT_WONDER_FONT, 12);
    //m_MenuOption->SetText("1-PLAYER GAME");

   // m_Transform->X = 270.0f;
   // m_Transform->Y = 400.0f;
    //m_MenuOption->Update(m_Transform, 0.0f);

	m_OnePlayer->Load(Assets::EIGHTBIT_WONDER_FONT, 12);
	m_OnePlayer->SetText("1-PLAYER GAME");
	m_Text1Transform->X = 270.0f;
	m_Text1Transform->Y = 400.0f;
	m_OnePlayer->Update(m_Text1Transform, 0.0f);

	m_TwoPlayer->Load(Assets::EIGHTBIT_WONDER_FONT, 12);
	m_TwoPlayer->SetText("2-PLAYER GAME");
	m_Text2Transform->X = 270.0f;
	m_Text2Transform->Y = 450.0f;
	m_TwoPlayer->Update(m_Text2Transform, 0.0f);



}

void MenuOption::Draw()
{
    IGraphic& tGraphic = GetGraphics();
	//MenuScreen tMenuScreen*;



    if(m_Flashing && m_Colored)
    {
		if (m_isPlayerOne)
		{
			tGraphic.SetColor(255, 0, 0, 255);
			m_OnePlayer->Draw();
		}
		else
		{
			tGraphic.SetColor(255, 0, 0, 255);
			m_TwoPlayer->Draw();
		}
    }

    tGraphic.SetColor(255, 255, 255, 255);
	
	if (m_Flashing && m_Colored)
	{
		if (m_isPlayerOne)
		{
			m_TwoPlayer->Draw();
		}
		else
		{
			m_OnePlayer->Draw();
		}
	}
	else
	{

		m_OnePlayer->Draw();
		m_TwoPlayer->Draw();
	}
    //m_MenuOption->Draw();

    tGraphic.SetColor(0, 0, 0, 255);
}

void MenuOption::Update(float aDeltaTime)
{
    if (IsKeyDown(KEY_RETURN) || Engine::Instance().GetInput().IsGamepadButtonDown(0, EControllerButton::A))
    {
        m_Flashing = true;
    }
	if (IsKeyDown(KEY_W))
	{
		if (!m_isPlayerOne)
		{
			m_isPlayerOne = true;
		}
	}
	else if (IsKeyDown(KEY_S))
	{
		if (m_isPlayerOne)
		{
			m_isPlayerOne = false;
		}
	}

    if (m_Flashing)
    {
        m_FlashTextElapsed += aDeltaTime;
        if (m_FlashTextElapsed >= m_FlashTextDelay)
        {
            m_FlashTextElapsed = 0.0f;
            m_FlashCount++;
            m_Colored = !m_Colored;
        }

        if (m_FlashCount > m_FlashNeeded)
        {
            Load("LevelOne");
        }
    }
}

void MenuOption::Destroy()
{
    IGraphic& tGraphic = GetGraphics();

    //m_MenuOption->Unload();
	m_OnePlayer->Unload();
	m_TwoPlayer->Unload();

   // SAFE_DELETE(m_MenuOption);
    //SAFE_DELETE(m_Transform);
	SAFE_DELETE(m_OnePlayer);
	SAFE_DELETE(m_Text1Transform);
	SAFE_DELETE(m_TwoPlayer);
	SAFE_DELETE(m_Text2Transform);
	


}
