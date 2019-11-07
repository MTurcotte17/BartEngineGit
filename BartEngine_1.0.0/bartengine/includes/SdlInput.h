#ifndef BART_SDL_INPUT_H
#define BART_SDL_INPUT_H

#include <IInput.h>
#include <vector>
#include <Point.h>

struct _SDL_Joystick;
struct SDL_JoyAxisEvent;

namespace bart
{
    class SdlInput final : public IInput
    {
    public:
        virtual ~SdlInput() = default;

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

    private:
        void UpdateGamepadButton(int aGamepad, int aButton, bool aDown);
        void UpdateGamepadAxis(SDL_JoyAxisEvent* aEvent);
        void UpdateTriggerAxis(SDL_JoyAxisEvent* aEvent);

        bool mMouseState[3]{false, false, false};
        const unsigned char* m_KeyStates{nullptr};
        int mMouseX{0};
        int mMouseY{0};

        std::vector<std::pair<Point*, Point*>> mStickValues;
        std::vector<std::pair<bool, bool>> mTriggerValues;
        std::vector<_SDL_Joystick*> mJoysticks;
        std::vector<std::vector<bool>> mGamepadButtonStates;
        bool mDPadState[4]{false, false, false, false};
        bool mHasGamepad{false};
        static const int mStickDeadZone{10000};
        static const int mTriggerDeadZone{-30000};
    };
}

#endif
