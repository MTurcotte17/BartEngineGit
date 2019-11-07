#include <Sprite.h>
#include <Engine.h>

void bart::Sprite::Load(const std::string& aFilename)
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    const unsigned int tTex = tGraphic.LoadTexture(aFilename);

    if (tTex != 0)
    {
        mTexId = tTex;

        int tW, tH;
        tGraphic.GetTextureSize(mTexId, &tW, &tH);

        m_Destination.Set(0, 0, tW, tH);
        m_Source.Set(0, 0, tW, tH);
    }
}

void bart::Sprite::Draw()
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.Draw(mTexId, m_Source, m_Destination, m_Angle, m_Flip, m_Alpha);
}

void bart::Sprite::Update(Transform* aTransform, float aDelta)
{
    if (aTransform != nullptr)
    {
        m_Destination.X = static_cast<int>(aTransform->X);
        m_Destination.Y = static_cast<int>(aTransform->Y);
        m_Destination.W = static_cast<int>(aTransform->Width);
        m_Destination.H = static_cast<int>(aTransform->Height);
        m_Angle = aTransform->Angle;
        m_Flip = aTransform->Flipped;
    }
}

void bart::Sprite::Unload()
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.UnloadTexture(mTexId);
}
