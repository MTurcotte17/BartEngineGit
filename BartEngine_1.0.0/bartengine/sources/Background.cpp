#include <Background.h>

void bart::Background::Load(const std::string& aFilename)
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    mTexId = tGraphic.LoadTexture(aFilename);

    m_DestinationA.Set(0, 0, tGraphic.GetScreenWidth(), tGraphic.GetScreenHeight());
    m_DestinationB.Set(0, m_DestinationA.Y + m_DestinationA.H, tGraphic.GetScreenWidth(), tGraphic.GetScreenHeight());

    int tW, tH;
    tGraphic.GetTextureSize(mTexId, &tW, &tH);
    m_SourceA.Set(0, 0, tW, tH);
    m_SourceB.Set(0, 0, tW, tH);
}

void bart::Background::Draw()
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.Draw(mTexId, m_SourceA, m_DestinationA, 0.0f, false, false, 255);
    tGraphic.Draw(mTexId, m_SourceB, m_DestinationB, 0.0f, false, false, 255);
}

void bart::Background::ScrollX(IGraphic& aGraphic, float aSpeed)
{
    const int tW = aGraphic.GetScreenWidth();

    m_DestinationA.X += static_cast<int>(aSpeed);
    m_DestinationB.X += static_cast<int>(aSpeed);

    if (aSpeed > 0)
    {
        if (m_DestinationA.X > tW)
        {
            int tRest = tW - m_DestinationA.X;
            m_DestinationA.X = 0 - m_DestinationA.W - tRest;
        }

        if (m_DestinationB.X > tW)
        {
            int tRest = tW - m_DestinationB.X;
            m_DestinationB.X = 0 - m_DestinationB.W - tRest;
        }
    }
    else
    {
        if ((m_DestinationA.X + m_DestinationA.W) < 0)
        {
            int tRest = (m_DestinationA.X + m_DestinationA.W);
            m_DestinationA.X = tW + tRest;
        }

        if ((m_DestinationB.X + m_DestinationB.W) < 0)
        {
            int tRest = (m_DestinationB.X + m_DestinationB.W);
            m_DestinationB.X = tW + tRest;
        }
    }
}

void bart::Background::ScrollY(IGraphic& aGraphic, float aSpeed)
{
    int tH = aGraphic.GetScreenHeight();

    m_DestinationA.Y += (int)aSpeed;
    m_DestinationB.Y += (int)aSpeed;

    if (aSpeed > 0)
    {
        if (m_DestinationA.Y > tH)
        {
            int tRest = tH - m_DestinationA.Y;
            m_DestinationA.Y = 0 - m_DestinationA.H - tRest;
        }

        if (m_DestinationB.Y > tH)
        {
            int tRest = tH - m_DestinationB.Y;
            m_DestinationB.Y = 0 - m_DestinationB.H - tRest;
        }
    }
    else
    {
        if ((m_DestinationA.Y + m_DestinationA.H) < 0)
        {
            int tRest = (m_DestinationA.Y + m_DestinationA.H);
            m_DestinationA.Y = tH + tRest;
        }

        if ((m_DestinationB.Y + m_DestinationB.H) < 0)
        {
            int tRest = (m_DestinationB.Y + m_DestinationB.H);
            m_DestinationB.Y = tH + tRest;
        }
    }
}

void bart::Background::Scroll(bool aHorizontal, float aSpeed)
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();

    if (aHorizontal)
    {
        ScrollX(tGraphic, aSpeed);
    }
    else
    {
        ScrollY(tGraphic, aSpeed);
    }
}

void bart::Background::Unload()
{
    IGraphic& tGraphic = Engine::Instance().GetGraphic();
    tGraphic.UnloadTexture(mTexId);
}
