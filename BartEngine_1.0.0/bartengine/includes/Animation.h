#ifndef BART_ANIMATION_H
#define BART_ANIMATION_H

#include <Sprite.h>

using namespace std;

namespace bart
{
    class Animation final : public Sprite
    {
    public:
        virtual ~Animation() = default;

        void InitAnimation(int aRows, int aWidth, int aHeight);
        void Draw() override;
        void Update(Transform* aTransform, float aDelta) override;
        void Play(int aStart, int aCount, float aDelay, bool aLoop);
        void Stop();

    private:
        void UpdateFrame();

        int m_ImagePerRow{0};
        int m_ImageWidth{0};
        int m_ImageHeight{0};
        int m_FirstFrame{0};
        int m_LastFrame{0};
        float m_Delay{0.0f};
        float m_Elapsed{0.0f};
        bool m_Playing{false};
        bool m_Loop{false};
        int m_CurrentFrame{0};
    };
}

#endif
