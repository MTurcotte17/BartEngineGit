#include <GameScreen.h>
#include "Assets.h"
#include <iostream>

void GameScreen::OnFallSpeedChange(float aSpeed)
{
    m_FallSpeed = 100.0f + ((1.0f - aSpeed) * 400.0f);
}

GameScreen::GameScreen()
{
    m_Background = new Sprite();
    m_Transform = new Transform();
    m_Theme = new Music();
    m_ThemeFast = new Music();
    m_GameOverTheme = new Music();
    m_Scrolling = new Background();
}

void GameScreen::Draw()
{
    IGraphic& tGraphic = GetGraphics();
    m_Scrolling->Draw();
    m_Background->Draw();
}

void GameScreen::Update(float aDeltaTime)
{
    m_Scrolling->Scroll(false, m_FallSpeed * aDeltaTime);
}

void GameScreen::Start()
{
    IGraphic& tGraphic = GetGraphics();
    m_Background->Load(Assets::BACKGROUND_GAMEPLAY);

    m_Transform->Width = static_cast<float>(tGraphic.GetScreenWidth());
    m_Transform->Height = static_cast<float>(tGraphic.GetScreenHeight());
    m_Background->Update(m_Transform, 0.0f);

    m_ThemeFast->Load(Assets::MUSIC_THEME_FAST);
    m_ThemeFast->SetVolumne(80);

    m_Theme->Load(Assets::MUSIC_THEME);
    m_Theme->SetVolumne(80);
    m_Theme->Play(-1);

    m_GameOverTheme->Load(Assets::GAMEOVER_THEME);
    m_GameOverTheme->SetVolumne(80);

    m_Scrolling->Load(Assets::SCROLLING_BACKGROUND);
}

void GameScreen::Destroy()
{
    IGraphic& tGraphic = GetGraphics();

    m_Theme->Stop();
    m_ThemeFast->Stop();
    m_GameOverTheme->Stop();

    m_Background->Unload();
    m_Theme->Unload();
    m_ThemeFast->Unload();
    m_GameOverTheme->Unload();
    m_Scrolling->Unload();

    SAFE_DELETE(m_Background);
    SAFE_DELETE(m_Transform);
    SAFE_DELETE(m_Theme);
    SAFE_DELETE(m_ThemeFast);
    SAFE_DELETE(m_GameOverTheme);
    SAFE_DELETE(m_Scrolling);
}

void GameScreen::OnLevelChange(int aLevel)
{
    if (aLevel >= 5)
    {
        m_Theme->Stop();
        m_ThemeFast->Play(-1);
    }
}

void GameScreen::OnGameOver()
{
    m_Theme->Stop();
    m_ThemeFast->Stop();

    m_GameOverTheme->Play(0);
}
