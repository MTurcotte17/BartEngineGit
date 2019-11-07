#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <Entity.h>
#include <Sprite.h>
#include <Music.h>
#include <Text.h>
#include "Background.h"

using namespace bart;

class GameScreen final : public Entity
{
public:
    virtual ~GameScreen() = default;
    void OnFallSpeedChange(float aSpeed);
    GameScreen();

    bool CanDraw() override { return true; }
    bool CanUpdate() override { return true; }

    void Draw() override;
    void Update(float aDeltaTime) override;
    void Start() override;
    void Destroy() override;

    void OnLevelChange(int aLevel);
    void OnGameOver();

private:

    Sprite* m_Background;
    Music* m_Theme;
    Music* m_ThemeFast;
    Music* m_GameOverTheme;
    Transform* m_Transform;
    Background* m_Scrolling;
    float m_FallSpeed{0.0f};
};

#endif
