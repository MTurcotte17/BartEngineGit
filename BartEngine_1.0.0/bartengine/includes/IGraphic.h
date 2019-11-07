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
        virtual void SetColor(int aRed, int aGreen, int aBlue, int aAlpha) = 0;
        virtual void SetClearColor(int aRed, int aGreen, int aBlue) = 0;

        virtual unsigned int LoadTexture(const string& aFilename) = 0;
        virtual void UnloadTexture(unsigned aTextureId) = 0;
        virtual unsigned int LoadFont(const string& aFilename, int aFontSize) = 0;
        virtual void UnloadFont(unsigned aFontId) = 0;

        virtual void Draw(const Rectangle& aRect) = 0;
        virtual void Draw(int aX, int aY, int aWidth, int aHeight) = 0;
        virtual void Draw(const Circle& aCircle) = 0;
        virtual void Draw(int aX, int aY, float aRadius) = 0;
        virtual void Draw(const Point& aPoint) = 0;
        virtual void Draw(int aX, int aY) = 0;

        virtual void Draw(unsigned int aTexture,
                          const Rectangle& aSrc,
                          const Rectangle& aDst,
                          float aAngle,
                          bool aFlip,
                          int aAlpha) = 0;
        virtual void Draw(unsigned int aFont, const std::string& aText, int aX, int aY) = 0;

        virtual void GetTextureSize(unsigned int aTextureId, int* aWidth, int* aHeight) = 0;
        virtual void GetFontSize(unsigned int aFontId, const string& aText, int* aWidth, int* aHeight) = 0;
        virtual int GetScreenWidth() const = 0;
        virtual int GetScreenHeight() const = 0;

        virtual int GetTextureInCache() const = 0;
        virtual int GetFontInCache() const = 0;

        virtual void SetCamera(Camera* aCamera) = 0;
    };
}

#endif
