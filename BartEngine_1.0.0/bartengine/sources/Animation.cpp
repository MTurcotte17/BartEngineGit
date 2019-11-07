#include <Animation.h>

void bart::Animation::InitAnimation(const int aRows, const int aWidth, const int aHeight)
{
    m_ImagePerRow = aRows;
    m_ImageWidth = aWidth;
    m_ImageHeight = aHeight;

    m_Destination.Set(0, 0, m_ImageWidth, m_ImageHeight);
    m_Source.Set(0, 0, m_ImageWidth, m_ImageHeight);
}

void bart::Animation::Update(Transform* aTransform, const float aDelta)
{
    Sprite::Update(aTransform, aDelta);

    if (m_Playing)
    {
        m_Elapsed += aDelta;
        if (m_Elapsed >= m_Delay)
        {
            m_Elapsed = 0.0f;

            m_CurrentFrame++;
            if (m_CurrentFrame > m_LastFrame)
            {
                m_CurrentFrame = m_FirstFrame;

                if (!m_Loop)
                {
                    m_Playing = false;
                }
            }

            UpdateFrame();
        }
    }
}

void bart::Animation::Draw()
{
    if (m_Playing)
    {
        Sprite::Draw();
    }
}

void bart::Animation::Play(const int aStart, const int aCount, const float aDelay, const bool aLoop)
{
    m_CurrentFrame = aStart;
    m_FirstFrame = aStart;
    m_LastFrame = aStart + aCount - 1;
    m_Delay = aDelay;
    m_Loop = aLoop;

    UpdateFrame();

    m_Playing = true;
}

void bart::Animation::Stop()
{
    m_Playing = false;

    m_CurrentFrame = 0;
    m_FirstFrame = 0;
    m_LastFrame = 0;
    m_Delay = 0.0f;
    m_Loop = false;
}

void bart::Animation::UpdateFrame()
{
    const int tRow = m_CurrentFrame / m_ImagePerRow;
    const int tCol = m_CurrentFrame - (m_ImagePerRow * tRow);
    const int tX = m_ImageWidth * tCol;
    const int tY = m_ImageHeight * tRow;

    m_Source.Set(tX, tY, m_ImageWidth, m_ImageHeight);
}
