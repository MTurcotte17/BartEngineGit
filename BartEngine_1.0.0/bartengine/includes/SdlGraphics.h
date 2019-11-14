#ifndef BART_SDLGRAPHICS_H
#define BART_SDLGRAPHICS_H

#include <IGraphic.h>
#include <map>
#include <Resource.h>
#include <Color.h>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Window;
typedef struct _TTF_Font TTF_Font;

namespace bart
{
    class SdlGraphics final : public IGraphic
    {
    public:
        SdlGraphics() = default;
        virtual ~SdlGraphics() = default;

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

        void Draw(size_t aFont, const std::string& aText, int aX, int aY) override;

        void GetTextureSize(size_t aTextureId, int* aWidth, int* aHeight) override;
        void GetFontSize(size_t aFontId, const string& aText, int* aWidth, int* aHeight) override;
        int GetScreenWidth() const override;
        int GetScreenHeight() const override;
        int GetTextureInCache() const override;
        int GetFontInCache() const override;
        void SetCamera(Camera* aCamera) override;

        void Fill(const Rectangle& aRect) override;
        void Fill(int aX, int aY, int aWidth, int aHeight) override;
    private:
        typedef map<size_t, Resource<SDL_Texture>*> TTexMap;
        typedef map<size_t, Resource<TTF_Font>*> TFontMap;

        TTexMap m_TexCache;
        TFontMap m_FntCache;

        SDL_Renderer* m_Renderer;
        SDL_Window* m_Window;
        Camera* m_Camera{nullptr};
        SDL_Texture* m_FontTexture{nullptr};

        int m_ScreenWidth{0};
        int m_ScreenHeight{0};
        Color m_ClearColor;
    };
}

#endif
