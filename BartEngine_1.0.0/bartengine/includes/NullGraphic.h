#ifndef BART_NULL_GRAPHICS_H
#define BART_NULL_GRAPHICS_H

#include <IGraphic.h>

namespace bart
{
    class NullGraphics final : public IGraphic
    {
    public:
        NullGraphics() = default;
        virtual ~NullGraphics() = default;

        bool Initialize() override;
        void Clean() override;

        bool InitWindow(const string& aTitle, int aWidth, int aHeight) override;
        void Clear() override;
        void Present() override;
        void SetColor(int aRed, int aGreen, int aBlue, int aAlpha) override;
        void SetClearColor(int aRed, int aGreen, int aBlue) override;

        unsigned LoadTexture(const string& aFilename) override;
        void UnloadTexture(unsigned aTextureId) override;
        unsigned LoadFont(const string& aFilename, int aFontSize) override;
        void UnloadFont(unsigned aFontId) override;

        void Draw(const Rectangle& aRect) override;
        void Draw(int aX, int aY, int aWidth, int aHeight) override;
        void Draw(const Circle& aCircle) override;
        void Draw(int aX, int aY, float aRadius) override;
        void Draw(const Point& aPoint) override;
        void Draw(int aX, int aY) override;
        void Draw(unsigned int aTexture,
                  const Rectangle& aSrc,
                  const Rectangle& aDst,
                  float aAngle,
                  bool aFlip,
                  int aAlpha) override;
        void Draw(unsigned int aFont, const string& aText, int aX, int aY) override;

        void GetTextureSize(unsigned int aTextureId, int* aWidth, int* aHeight) override;
        void GetFontSize(unsigned int aFontId, const string& aText, int* aWidth, int* aHeight) override;
        int GetScreenWidth() const override;
        int GetScreenHeight() const override;
        int GetTextureInCache() const override;
        int GetFontInCache() const override;
        void SetCamera(Camera* aCamera) override;
    };
}

#endif
