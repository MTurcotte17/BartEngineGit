#include <NullGraphic.h>

bool bart::NullGraphics::Initialize()
{
    return true;
}

void bart::NullGraphics::Clean()
{
}

bool bart::NullGraphics::InitWindow(const string& /*aTitle*/, int /*aWidth*/, int /*aHeight*/)
{
    return true;
}

void bart::NullGraphics::Clear()
{
}

void bart::NullGraphics::Present()
{
}

void bart::NullGraphics::SetColor(unsigned char /*aRed*/,
                                  unsigned char /*aGreen*/,
                                  unsigned char /*aBlue*/,
                                  unsigned char /*aAlpha*/)
{
}

void bart::NullGraphics::SetClearColor(unsigned char /*aRed*/, unsigned char /*aGreen*/, unsigned char /*aBlue*/)
{
}

size_t bart::NullGraphics::LoadTexture(const string& /*aFilename*/)
{
    return 0;
}

void bart::NullGraphics::UnloadTexture(size_t /*aTextureId*/)
{
}

size_t bart::NullGraphics::LoadFont(const string& /*aFilename*/, int /*aFontSize*/)
{
    return 0;
}

void bart::NullGraphics::UnloadFont(size_t /*aFontId*/)
{
}

void bart::NullGraphics::Draw(const Rectangle& /*aRect*/)
{
}

void bart::NullGraphics::Draw(int /*aX*/, int /*aY*/, int /*aWidth*/, int /*aHeight*/)
{
}

void bart::NullGraphics::Draw(const Circle& /*aCircle*/)
{
}

void bart::NullGraphics::Draw(int /*aX*/, int /*aY*/, float /*aRadius*/)
{
}

void bart::NullGraphics::Draw(const Point& /*aPoint*/)
{
}

void bart::NullGraphics::Draw(int /*aX*/, int /*aY*/)
{
}

void bart::NullGraphics::Draw(size_t /*aTexture*/,
                              const Rectangle& /*aSrc*/,
                              const Rectangle& /*aDst*/,
                              float /*aAngle*/,
                              bool /*aHorizontalFlip*/,
                              bool /*aVerticalFlip*/,
                              unsigned char /*aAlpha*/)
{
}

void bart::NullGraphics::Draw(size_t /*aFont*/, const string& /*aText*/, int /*aX*/, int /*aY*/)
{
}

void bart::NullGraphics::GetTextureSize(size_t /*aTextureId*/, int* /*aWidth*/, int* /*aHeight*/)
{
}

void bart::NullGraphics::GetFontSize(size_t /*aFontId*/, const string& /*aText*/, int* /*aWidth*/, int* /*aHeight*/)
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

void bart::NullGraphics::SetCamera(Camera* /*aCamera*/)
{
}

void bart::NullGraphics::Fill(const Rectangle& /*aRect*/)
{
}

void bart::NullGraphics::Fill(int /*aX*/, int /*aY*/, int /*aWidth*/, int /*aHeight*/)
{
}
