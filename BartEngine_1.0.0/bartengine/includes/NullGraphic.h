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
        void SetColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue, unsigned char aAlpha) override;
        void SetClearColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue) override;

        size_t LoadTexture(const string& aFilename) override;
        void UnloadTexture(size_t aTextureId) override;
        size_t LoadFont(const string& aFilename, int aFontSize) override;
        void UnloadFont(size_t aFontId) override;

        void Draw(const Rectangle& aRect) override;
        void Draw(int aX, int aY, int aWidth, int aHeight) override;
        void Draw(const Circle& aCircle) override;
        void Draw(int aX, int aY, float aRadius) override;
        void Draw(const Point& aPoint) override;
        void Draw(int aX, int aY) override;
        void Draw(size_t aTexture,
                  const Rectangle& aSrc,
                  const Rectangle& aDst,
                  float aAngle,
                  bool aHorizontalFlip,
                  bool aVerticalFlip,
                  unsigned char aAlpha) override;
        void Draw(size_t aFont, const string& aText, int aX, int aY) override;

        void GetTextureSize(size_t aTextureId, int* aWidth, int* aHeight) override;
        void GetFontSize(size_t aFontId, const string& aText, int* aWidth, int* aHeight) override;
        int GetScreenWidth() const override;
        int GetScreenHeight() const override;
        int GetTextureInCache() const override;
        int GetFontInCache() const override;
        void SetCamera(Camera* aCamera) override;
        void Fill(const Rectangle& aRect) override;
        void Fill(int aX, int aY, int aWidth, int aHeight) override;
    };
}

#endif
