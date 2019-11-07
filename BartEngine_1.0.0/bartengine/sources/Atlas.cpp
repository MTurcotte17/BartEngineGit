#include <Atlas.h>

void bart::Atlas::AddFrame(const std::string& aName, const int aX, const int aY, const int aWidth, const int aHeight)
{
    if (m_Frames.count(aName) == 0)
    {
        m_Frames[aName].Set(aX, aY, aWidth, aHeight);
    }
}

void bart::Atlas::SetFrame(const std::string& aName)
{
    if (m_Frames.count(aName) > 0)
    {
        const Rectangle tRect = m_Frames[aName];
        m_Source.Set(tRect.X, tRect.Y, tRect.W, tRect.H);
    }
}
