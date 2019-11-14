#include <Text.h>

void bart::Text::Load(const string& aFontFile, int aFontSize)
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    m_FontId = tGraphic.LoadFont(aFontFile, aFontSize);
}

void bart::Text::Load(const string& aFontFile)
{
    Load(aFontFile, 12);
}

void bart::Text::Draw()
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.Draw(m_FontId, m_Text, m_X, m_Y);
}

void bart::Text::Update(Transform* aTransform, float /*aDelta*/)
{
    if (aTransform != nullptr)
    {
        m_X = static_cast<int>(aTransform->X);
        m_Y = static_cast<int>(aTransform->Y);
    }
}

void bart::Text::Unload()
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.UnloadFont(m_FontId);
}
