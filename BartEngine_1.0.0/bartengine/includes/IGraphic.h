#ifndef BART_IGRAPHIC_H
#define BART_IGRAPHIC_H

#include <IService.h>
#include <Rectangle.h>
#include <Point.h>
#include <Circle.h>
#include <string>

using namespace std;

namespace bart
{
    class Camera;

    class IGraphic : public IService
    {
    public:
        virtual ~IGraphic() = default;

        virtual bool InitWindow(const string& aTitle, int aWidth, int aHeight) = 0;
        virtual void Clear() = 0;
        virtual void Present() = 0;
        virtual void SetColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue, unsigned char aAlpha) = 0;
        virtual void SetClearColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue) = 0;

        virtual size_t LoadTexture(const string& aFilename) = 0;
        virtual void UnloadTexture(size_t aTextureId) = 0;
        virtual size_t LoadFont(const string& aFilename, int aFontSize) = 0;
        virtual void UnloadFont(size_t aFontId) = 0;

        virtual void Draw(const Rectangle& aRect) = 0;
        virtual void Fill(const Rectangle& aRect) = 0;

        virtual void Draw(int aX, int aY, int aWidth, int aHeight) = 0;
        virtual void Fill(int aX, int aY, int aWidth, int aHeight) = 0;

        virtual void Draw(const Circle& aCircle) = 0;
        virtual void Draw(int aX, int aY, float aRadius) = 0;
        virtual void Draw(const Point& aPoint) = 0;
        virtual void Draw(int aX, int aY) = 0;

        virtual void Draw(size_t aTexture,
                          const Rectangle& aSrc,
                          const Rectangle& aDst,
                          float aAngle,
                          bool aHorizontalFlip,
                          bool aVerticalFlip,
                          unsigned char aAlpha) = 0;
        virtual void Draw(size_t aFont, const std::string& aText, int aX, int aY) = 0;

        virtual void GetTextureSize(size_t aTextureId, int* aWidth, int* aHeight) = 0;
        virtual void GetFontSize(size_t aFontId, const string& aText, int* aWidth, int* aHeight) = 0;
        virtual int GetScreenWidth() const = 0;
        virtual int GetScreenHeight() const = 0;

        virtual int GetTextureInCache() const = 0;
        virtual int GetFontInCache() const = 0;

        virtual void SetCamera(Camera* aCamera) = 0;
    };
}

#endif
