#ifndef BOARD_CONTROL_H
#define BOARD_CONTROL_H

#include <Component.h>
#include <Board.h>

class BoardControl final : public Component
{
public:
    virtual ~BoardControl() = default;

    void Update(Board& aBoard, float aDeltaTime);

private:
    bool m_MovePressed{false};
    bool m_RotatePressed{false};
    bool m_HotFallPressed{false};

    float m_TranslateDelay{ 0.15f };
    float m_TranslateElapsed{0.0f};
};
#endif
