#ifndef MENUOPTION_H
#define MENUOPTION_H

#include <Entity.h>
#include <Text.h>

using namespace bart;

class MenuOption final : public Entity
{
public:
    virtual ~MenuOption() = default;
    MenuOption();

    bool CanDraw() override { return true; }
    bool CanUpdate() override { return true; }
    void Draw() override;
    void Start() override;
    void Update(float aDeltaTime) override;
    void Destroy() override;

private:
    Text* m_MenuOption{nullptr};
	Text* m_OnePlayer{ nullptr };
	Text* m_TwoPlayer{ nullptr };
    Transform* m_Transform{nullptr};
	Transform* m_Text1Transform{ nullptr };
	Transform* m_Text2Transform{ nullptr };
	Transform* m_BalloonTransform{ nullptr };
	bool m_isPlayerOne = true;
    float m_FlashTextDelay{0.05f};
    float m_FlashTextElapsed{0.0f};
    bool m_Flashing{false};
    bool m_Colored{false};
    int m_FlashCount{0};
    const int m_FlashNeeded = 6;
};

#endif
