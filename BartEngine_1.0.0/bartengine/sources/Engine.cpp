#include <Engine.h>
#include <Config.h>
#include <iostream>

bool bart::Engine::Initialize(const std::string& aTitle, const int aWidth, const int aHeight)
{
    if (!m_IsInitialized)
    {
        CREATE_LOGGER(m_LoggerService);

        if (!m_LoggerService->Initialize())
        {
            m_LoggerService = new NullLogger();
            if (!m_LoggerService->Initialize())
            {
                std::cout << "Impossible to initialize the logger service" << std::endl;
            }
        }

        m_LoggerService->Log("**** Starting engine version %s ****\n", BART_ENGINE_VERSION_STRING);

        CREATE_GRAPHIC(m_GraphicService);
        CREATE_AUDIO(m_AudioService);
        CREATE_INPUT(m_InputService);
        CREATE_TIMER(m_TimerService);
        CREATE_SCENE(m_SceneService);
        CREATE_COLLISION(m_CollisionService);

        if (!m_GraphicService->Initialize())
        {
            m_GraphicService = new NullGraphics();
            if (!m_GraphicService->Initialize())
            {
                m_LoggerService->Log("Impossible to initialize the graphic services");
                return false;
            }
        }

        if (!m_AudioService->Initialize())
        {
            m_AudioService = new NullAudio();
            if (!m_AudioService->Initialize())
            {
                m_LoggerService->Log("Impossible to initialize the audio services");
                return false;
            }
        }

        if (!m_InputService->Initialize())
        {
            m_InputService = new NullInput();
            if (!m_InputService->Initialize())
            {
                m_LoggerService->Log("Impossible to initialize the input services");
                return false;
            }
        }

        if (!m_TimerService->Initialize())
        {
            m_TimerService = new NullTimer();
            if (!m_TimerService->Initialize())
            {
                m_LoggerService->Log("Impossible to initialize the timer services");
                return false;
            }
        }

        if (!m_SceneService->Initialize())
        {
            m_SceneService = new NullScene();
            if (!m_SceneService->Initialize())
            {
                m_LoggerService->Log("Impossible to initialize the scene services");
                return false;
            }
        }

        if (!m_CollisionService->Initialize())
        {
            m_CollisionService = new NullCollision();
            if (!m_CollisionService->Initialize())
            {
                m_LoggerService->Log("Impossible to initialize the collision services");
                return false;
            }
        }

        if (!m_GraphicService->InitWindow(aTitle, aWidth, aHeight))
        {
            m_LoggerService->Log("Impossible to create a window");
            return false;
        }

        m_IsInitialized = true;
    }

    return m_IsInitialized;
}

void bart::Engine::Clean()
{
    SAFE_CLEAN(m_CollisionService);
    SAFE_CLEAN(m_SceneService);
    SAFE_CLEAN(m_InputService);
    SAFE_CLEAN(m_AudioService);
    SAFE_CLEAN(m_GraphicService);
    SAFE_CLEAN(m_TimerService);
    SAFE_CLEAN(m_LoggerService);
}

void bart::Engine::Start()
{
    if (m_IsInitialized && !m_IsRunning)
    {
        m_IsRunning = true;
        float tLastTime = m_TimerService->GetTime();

        while (m_IsRunning)
        {
            const float tCurrent = m_TimerService->GetTime();
            const float tElapsed = tCurrent - tLastTime;

            ProcessInput();
            Update(tElapsed * 0.001f);
            Render();

            const float tEnd = m_TimerService->GetTime();
            m_TimerService->Wait(tCurrent + 16.66667f - tEnd);
            tLastTime = tCurrent;

#ifdef USE_NULL_ENGINE
            Stop();
#endif
        }

        Stop();
    }

    Clean();
}

void bart::Engine::Stop()
{
    m_IsRunning = false;
}

void bart::Engine::ProcessInput() const
{
    m_InputService->PoolEvents();

#ifdef _DEBUG
    static bool tResetPressed = false;
    if (m_InputService->IsKeyDown(KEY_F5))
    {
        if (!tResetPressed)
        {
            tResetPressed = true;
            m_SceneService->Reset();
        }
    }
    else
    {
        tResetPressed = false;
    }
#endif
}

void bart::Engine::Update(const float aDeltaTime) const
{
    m_SceneService->Update(aDeltaTime);
}

void bart::Engine::Render() const
{
    m_GraphicService->Clear();
    m_SceneService->Draw();
    m_GraphicService->Present();
}
