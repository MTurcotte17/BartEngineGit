#include <BoardControl.h>
#include <Engine.h>
#include <iostream>

void BoardControl::Update(Board& aBoard, float aDeltaTime)
{
    IInput& tInput = Engine::Instance().GetInput();

    if (tInput.IsKeyDown(KEY_DOWN) || tInput.IsGamepadButtonDown(0, EControllerButton::A))
    {
        if (!m_HotFallPressed)
        {
            m_HotFallPressed = true;
            aBoard.FastFall();
        }
    }
    else
    {
        m_HotFallPressed = false;
        aBoard.NormalFall();
    }

    const int tAxisX = Engine::Instance().GetInput().GetGamepadAxisX(0, 1);

    if (tInput.IsKeyDown(KEY_LEFT) || tAxisX < 0)
    {
        if (!m_MovePressed)
        {
            m_MovePressed = true;
            m_TranslateElapsed = 0.0f;
            aBoard.Translate(-1);
        }
        else
        {
            m_TranslateElapsed += aDeltaTime;
            if(m_TranslateElapsed >= m_TranslateDelay)
            {
                m_TranslateElapsed = 0.0f;
                aBoard.Translate(-1);
            }
        }
    }
    else if (tInput.IsKeyDown(KEY_RIGHT) || tAxisX > 0)
    {
        if (!m_MovePressed)
        {
            m_TranslateElapsed = 0.0f;
            m_MovePressed = true;
            aBoard.Translate(1);
        }
        else
        {
            m_TranslateElapsed += aDeltaTime;
            if (m_TranslateElapsed >= m_TranslateDelay)
            {
                m_TranslateElapsed = 0.0f;
                aBoard.Translate(1);
            }
        }
    }
    else if (m_MovePressed)
    {
        m_MovePressed = false;
    }

    if (tInput.IsKeyDown(KEY_UP) || tInput.IsGamepadButtonDown(0, EControllerButton::X))
    {
        if (!m_RotatePressed)
        {
            m_RotatePressed = true;
            aBoard.Rotate();
        }
    }
    else if (m_RotatePressed)
    {
        m_RotatePressed = false;
    }

    if (tInput.IsKeyDown(KEY_ESCAPE) || tInput.IsGamepadButtonDown(0, EControllerButton::Y))
    {
        Engine::Instance().GetScene().Load("MainMenu");
    }
}