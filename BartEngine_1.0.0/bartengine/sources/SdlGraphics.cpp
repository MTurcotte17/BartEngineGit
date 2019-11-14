#include <SdlGraphics.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Engine.h>
#include <Camera.h>
#include <iostream>

bool bart::SdlGraphics::Initialize()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        Engine::Instance().GetLogger().Log("Cannot initialize SDL\n");
        return false;
    }

    const int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        Engine::Instance().GetLogger().Log("Cannot initialize SDL_image\n");
        return false;
    }

    if (TTF_Init() < 0)
    {
        Engine::Instance().GetLogger().Log("Cannot initialize SDL_ttf\n");
        return false;
    }

    m_ClearColor.Set(0, 0, 0, 255);

    return true;
}

void bart::SdlGraphics::Clean()
{
    if (m_FontTexture != nullptr)
    {
        SDL_DestroyTexture(m_FontTexture);
        m_FontTexture = nullptr;
    }

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

    m_Renderer = nullptr;
    m_Window = nullptr;

    for (TTexMap::iterator it = m_TexCache.begin(); it != m_TexCache.end(); ++it)
    {
        SDL_DestroyTexture(it->second->Data);
        delete it->second;
    }

    for (TFontMap::iterator it = m_FntCache.begin(); it != m_FntCache.end(); ++it)
    {
        TTF_CloseFont(it->second->Data);
        delete it->second;
    }

    m_TexCache.clear();
    m_FntCache.clear();

    TTF_Quit();
    SDL_Quit();
}

bool bart::SdlGraphics::InitWindow(const string& aTitle, const int aWidth, const int aHeight)
{
    m_Window = SDL_CreateWindow(aTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, aWidth, aHeight, 0);

    if (m_Window == nullptr)
    {
        Engine::Instance().GetLogger().Log("Cannot initialize SDL window\n");
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

    if (m_Renderer == nullptr)
    {
        Engine::Instance().GetLogger().Log("Cannot initialize SDL renderer\n");
        return false;
    }

    m_ScreenWidth = aWidth;
    m_ScreenHeight = aHeight;
    SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
    return true;
}

void bart::SdlGraphics::Clear()
{
    SDL_SetRenderDrawColor(m_Renderer, m_ClearColor.R, m_ClearColor.G, m_ClearColor.B, 255);
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
}

void bart::SdlGraphics::Present()
{
    SDL_RenderPresent(m_Renderer);
}

void bart::SdlGraphics::SetColor(const unsigned char aRed,
                                 const unsigned char aGreen,
                                 const unsigned char aBlue,
                                 const unsigned char aAlpha)
{
    SDL_SetRenderDrawColor(m_Renderer, aRed, aGreen, aBlue, aAlpha);
}

void bart::SdlGraphics::SetClearColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue)
{
    m_ClearColor.Set(aRed, aGreen, aBlue, 255);
}

size_t bart::SdlGraphics::LoadTexture(const string& aFilename)
{
    const size_t tHashKey = std::hash<std::string>()(aFilename);

    if (m_TexCache.count(tHashKey) > 0)
    {
        m_TexCache[tHashKey]->Count++;
        return tHashKey;
    }

    SDL_Surface* tSurface = IMG_Load(aFilename.c_str());
    if (tSurface != nullptr)
    {
        SDL_Texture* tTex = nullptr;
        tTex = SDL_CreateTextureFromSurface(m_Renderer, tSurface);
        SDL_FreeSurface(tSurface);

        if (tTex != nullptr)
        {
            m_TexCache[tHashKey] = new Resource<SDL_Texture>();
            m_TexCache[tHashKey]->Data = tTex;
            m_TexCache[tHashKey]->Count = 1;
            return tHashKey;
        }
    }

    Engine::Instance().GetLogger().Log("Cannot load texture: %s\n", aFilename.c_str());
    return 0;
}

void bart::SdlGraphics::UnloadTexture(size_t aTextureId)
{
    if (m_TexCache.count(aTextureId) > 0)
    {
        m_TexCache[aTextureId]->Count--;
        if (m_TexCache[aTextureId]->Count <= 0)
        {
            SDL_DestroyTexture(m_TexCache[aTextureId]->Data);
            delete m_TexCache[aTextureId];
            m_TexCache.erase(aTextureId);
        }
    }
}

size_t bart::SdlGraphics::LoadFont(const string& aFilename, int aFontSize)
{
    const std::string tFontName = aFilename + "_" + std::to_string(aFontSize);
    const size_t tHashKey = std::hash<std::string>()(tFontName);

    if (m_FntCache.count(tHashKey) > 0)
    {
        m_FntCache[tHashKey]->Count++;
        return tHashKey;
    }

    TTF_Font* tFont = TTF_OpenFont(aFilename.c_str(), aFontSize * 2);

    if (tFont != nullptr)
    {
        m_FntCache[tHashKey] = new Resource<TTF_Font>();
        m_FntCache[tHashKey]->Data = tFont;
        m_FntCache[tHashKey]->Count = 1;
        return tHashKey;
    }

    return 0;
}

void bart::SdlGraphics::UnloadFont(size_t aFontId)
{
    if (m_FntCache.count(aFontId) > 0)
    {
        m_FntCache[aFontId]->Count--;
        if (m_FntCache[aFontId]->Count <= 0)
        {
            TTF_CloseFont(m_FntCache[aFontId]->Data);
            delete m_FntCache[aFontId];
            m_FntCache.erase(aFontId);
        }
    }
}

void bart::SdlGraphics::Draw(const Rectangle& aRect)
{
    int x, y, w, h;
    aRect.Get(&x, &y, &w, &h);
    Draw(x, y, w, h);
}

void bart::SdlGraphics::Draw(const int aX, const int aY, const int aWidth, const int aHeight)
{
    SDL_Rect tRect = {aX, aY, aWidth, aHeight};

    if (m_Camera != nullptr)
    {
        tRect.x -= m_Camera->GetX();
        tRect.y -= m_Camera->GetY();
    }

    SDL_RenderDrawRect(m_Renderer, &tRect);
}

void bart::SdlGraphics::Draw(const Circle& aCircle)
{
    int x, y;
    float r;
    aCircle.Get(&x, &y, &r);
    Draw(x, y, r);
}

void bart::SdlGraphics::Draw(const int aX, const int aY, const float aRadius)
{
    float tError = -aRadius;
    float tX = aRadius - 0.5f;
    float tY = 0.5f;
    float tCx = aX - 0.5f;
    float tCy = aY - 0.5f;

    if (m_Camera != nullptr)
    {
        tCx = aX - m_Camera->GetX() - 0.5f;
        tCy = aY - m_Camera->GetY() - 0.5f;
    }

    while (tX >= tY)
    {
        Draw(static_cast<int>(tCx + tX), static_cast<int>(tCy + tY));
        Draw(static_cast<int>(tCx + tY), static_cast<int>(tCy + tX));

        if (tX != 0)
        {
            Draw(static_cast<int>(tCx - tX), static_cast<int>(tCy + tY));
            Draw(static_cast<int>(tCx + tY), static_cast<int>(tCy - tX));
        }

        if (tY != 0)
        {
            Draw(static_cast<int>(tCx + tX), static_cast<int>(tCy - tY));
            Draw(static_cast<int>(tCx - tY), static_cast<int>(tCy + tX));
        }

        if (tX != 0 && tY != 0)
        {
            Draw(static_cast<int>(tCx - tX), static_cast<int>(tCy - tY));
            Draw(static_cast<int>(tCx - tY), static_cast<int>(tCy - tX));
        }

        tError += tY;
        ++tY;
        tError += tY;

        if (tError >= 0)
        {
            --tX;
            tError -= tX;
            tError -= tX;
        }
    }
}

void bart::SdlGraphics::Draw(const Point& aPoint)
{
    Draw(aPoint.X, aPoint.Y);
}

void bart::SdlGraphics::Draw(const int aX, const int aY)
{
    int tX = aX;
    int tY = aY;

    if (m_Camera != nullptr)
    {
        tX -= m_Camera->GetX();
        tY -= m_Camera->GetY();
    }

    SDL_RenderDrawPoint(m_Renderer, tX, tY);
}

void bart::SdlGraphics::Draw(size_t aTexture,
                             const Rectangle& aSrc,
                             const Rectangle& aDst,
                             float aAngle,
                             bool aHorizontalFlip,
                             bool aVerticalFlip,
                             unsigned char aAlpha)
{
    if (aTexture)
    {
        SDL_Rect tSrcRect = {aSrc.X, aSrc.Y, aSrc.W, aSrc.H};
        SDL_Rect tDstRect = {aDst.X, aDst.Y, aDst.W, aDst.H};

        int tFlipValue = SDL_FLIP_NONE;

        if (aHorizontalFlip)
        {
            tFlipValue |= SDL_FLIP_HORIZONTAL;
        }

        if (aVerticalFlip)
        {
            tFlipValue |= SDL_FLIP_VERTICAL;
        }

        const SDL_RendererFlip tFlip = static_cast<SDL_RendererFlip>(tFlipValue);

        SDL_Texture* tTex = m_TexCache[aTexture]->Data;

        if (m_Camera != nullptr)
        {
            tDstRect.x -= m_Camera->GetX();
            tDstRect.y -= m_Camera->GetY();
        }

        SDL_SetTextureBlendMode(tTex, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(tTex, aAlpha);
        SDL_RenderCopyEx(m_Renderer, tTex, &tSrcRect, &tDstRect, aAngle, nullptr, tFlip);
    }
}

void bart::SdlGraphics::Draw(size_t aFont, const std::string& aText, int aX, int aY)
{
    if (aFont)
    {
        SDL_Color tColor;
        SDL_GetRenderDrawColor(m_Renderer, &tColor.r, &tColor.g, &tColor.b, &tColor.a);

        TTF_Font* tFnt = m_FntCache[aFont]->Data;
        SDL_Surface* tSurface = TTF_RenderText_Solid(tFnt, aText.c_str(), tColor);

        if (tSurface != nullptr)
        {
            if (m_FontTexture != nullptr)
            {
                SDL_DestroyTexture(m_FontTexture);
                m_FontTexture = nullptr;
            }

            m_FontTexture = SDL_CreateTextureFromSurface(m_Renderer, tSurface);
            SDL_FreeSurface(tSurface);

            if (m_FontTexture != nullptr)
            {
                int w = 0;
                int h = 0;
                SDL_QueryTexture(m_FontTexture, nullptr, nullptr, &w, &h);
                SDL_Rect tDestination = {aX, aY, w, h};

                if (m_Camera != nullptr)
                {
                    tDestination.x -= m_Camera->GetX();
                    tDestination.y -= m_Camera->GetY();
                }

                SDL_RenderCopy(m_Renderer, m_FontTexture, nullptr, &tDestination);
            }
        }
    }
}

void bart::SdlGraphics::GetTextureSize(size_t aTextureId, int* aWidth, int* aHeight)
{
    if (m_TexCache.count(aTextureId) > 0)
    {
        SDL_Texture* tTexture = m_TexCache[aTextureId]->Data;
        SDL_QueryTexture(tTexture, nullptr, nullptr, aWidth, aHeight);
    }
    else
    {
        *aWidth = 0;
        *aHeight = 0;
    }
}

void bart::SdlGraphics::GetFontSize(size_t aFontId, const string& aText, int* aWidth, int* aHeight)
{
    if (m_FntCache.count(aFontId) > 0)
    {
        TTF_Font* tFont = m_FntCache[aFontId]->Data;
        TTF_SizeText(tFont, aText.c_str(), aWidth, aHeight);
    }
    else
    {
        *aWidth = 0;
        *aHeight = 0;
    }
}

int bart::SdlGraphics::GetScreenWidth() const
{
    return m_ScreenWidth;
}

int bart::SdlGraphics::GetScreenHeight() const
{
    return m_ScreenHeight;
}

int bart::SdlGraphics::GetTextureInCache() const
{
    return static_cast<int>(m_TexCache.size());
}

int bart::SdlGraphics::GetFontInCache() const
{
    return static_cast<int>(m_FntCache.size());
}

void bart::SdlGraphics::SetCamera(Camera* aCamera)
{
    m_Camera = aCamera;
}

void bart::SdlGraphics::Fill(const Rectangle& aRect)
{
    int x, y, w, h;
    aRect.Get(&x, &y, &w, &h);
    Fill(x, y, w, h);
}

void bart::SdlGraphics::Fill(int aX, int aY, int aWidth, int aHeight)
{
    SDL_Rect tRect = {aX, aY, aWidth, aHeight};

    if (m_Camera != nullptr)
    {
        tRect.x -= m_Camera->GetX();
        tRect.y -= m_Camera->GetY();
    }

    SDL_RenderFillRect(m_Renderer, &tRect);
}
