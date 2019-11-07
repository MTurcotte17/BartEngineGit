#ifndef BART_NULL_INPUT_H
#define BART_NULL_INPUT_H

#include <IInput.h>

namespace bart
{
    class NullInput final : public IInput
    {
    public:
        virtual ~NullInput() = default;

        bool Initialize() override;
        void Clean() override;

        void PoolEvents() override;
        bool IsKeyDown(EKeys aKey) override;
        bool IsMouseButtonDown(EMouseButton aButton) override;
        int GetMouseX() const override;
        int GetMouseY() const override;
        bool IsGamepadButtonDown(int aGamepad, EControllerButton aButton) const override;
        int GetGamepadAxisX(int aGamePad, int aStick) const override;
        int GetGamepadAxisY(int aGamePad, int aStick) const override;
        bool IsTriggerDown(int aGamePad, int aTrigger) override;
    };
}

#endif
