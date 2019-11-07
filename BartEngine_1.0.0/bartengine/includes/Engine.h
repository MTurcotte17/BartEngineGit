#ifndef BART_ENGINE_H
#define BART_ENGINE_H

#include <IAudio.h>
#include <IGraphic.h>
#include <IInput.h>
#include <ITimer.h>
#include <IScene.h>
#include <ILogger.h>
#include <Config.h>
#include <string>
#include <ICollision.h>

namespace bart
{
    class Engine
    {
    public:
        static Engine& Instance()
        {
            static Engine instance;
            return instance;
        }

        bool Initialize(const std::string& aTitle, int aWidth, int aHeight);
        void Start();
        void Stop();
        void ProcessInput() const;
        void Update(float aDeltaTime) const;
        void Render() const;

        IAudio& GetAudio() const { return *m_AudioService; }
        IGraphic& GetGraphic() const { return *m_GraphicService; }
        IInput& GetInput() const { return *m_InputService; }
        ITimer& GetTimer() const { return *m_TimerService; }
        ILogger& GetLogger() const { return *m_LoggerService; }
        IScene& GetScene() const { return *m_SceneService; }
        ICollision& GetCollision() const { return *m_CollisionService; }

    private:
        Engine()
        {
        }

        IAudio* m_AudioService{nullptr};
        IGraphic* m_GraphicService{nullptr};
        IInput* m_InputService{nullptr};
        ITimer* m_TimerService{nullptr};
        ILogger* m_LoggerService{nullptr};
        IScene* m_SceneService{nullptr};
        ICollision* m_CollisionService{nullptr};

        void Clean();

        bool m_IsInitialized{false};
        bool m_IsRunning{false};
    };
}

#endif
