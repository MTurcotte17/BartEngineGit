#include <NullGraphic.h>

bool bart::NullGraphics::Initialize()
{
    return true;
}

void bart::NullGraphics::Clean()
{
}

bool bart::NullGraphics::InitWindow(const string& aTitle, int aWidth, int aHeight)
{
    return true;
}

void bart::NullGraphics::Clear()
{
}

void bart::NullGraphics::Present()
{
}

void bart::NullGraphics::SetColor(int aRed, int aGreen, int aBlue, int aAlpha)
{
}

void bart::NullGraphics::SetClearColor(int aRed, int aGreen, int aBlue)
{
}

unsigned bart::NullGraphics::LoadTexture(const string& aFilename)
{
    return 0;
}

void bart::NullGraphics::UnloadTexture(unsigned aTextureId)
{
}

unsigned bart::NullGraphics::LoadFont(const string& aFilename, int aFontSize)
{
    return 0;
}

void bart::NullGraphics::UnloadFont(unsigned aFontId)
{
}

void bart::NullGraphics::Draw(const Rectangle& aRect)
{
}

void bart::NullGraphics::Draw(int aX, int aY, int aWidth, int aHeight)
{
}

void bart::NullGraphics::Draw(const Circle& aCircle)
{
}

void bart::NullGraphics::Draw(int aX, int aY, float aRadius)
{
}

void bart::NullGraphics::Draw(const Point& aPoint)
{
}

void bart::NullGraphics::Draw(int aX, int aY)
{
}

void bart::NullGraphics::Draw(unsigned aTexture,
                              const Rectangle& aSrc,
                              const Rectangle& aDst,
                              float aAngle,
                              bool aFlip,
                              int aAlpha)
{
}

void bart::NullGraphics::Draw(unsigned aFont, const string& aText, int aX, int aY)
{
}

void bart::NullGraphics::GetTextureSize(unsigned aTextureId, int* aWidth, int* aHeight)
{
}

void bart::NullGraphics::GetFontSize(unsigned aFontId, const string& aText, int* aWidth, int* aHeight)
{
}

int bart::NullGraphics::GetScreenWidth() const
{
    return 0;
}

int bart::NullGraphics::GetScreenHeight() const
{
    return 0;
}

int bart::NullGraphics::GetTextureInCache() const
{
    return 0;
}

int bart::NullGraphics::GetFontInCache() const
{
    return 0;
}

void bart::NullGraphics::SetCamera(Camera* aCamera)
{
}
