#ifndef BART_IINPUT_H
#define BART_IINPUT_H

#include <EKeys.h>
#include <IService.h>
#include <EMouseButton.h>
#include <EControllerButtons.h>

namespace bart
{
    class IInput : public IService
    {
    public:
        virtual ~IInput() = default;

        virtual void PoolEvents() = 0;
        virtual bool IsKeyDown(EKeys aKey) = 0;
        virtual bool IsMouseButtonDown(EMouseButton aButton) = 0;
        virtual int GetMouseX() const = 0;
        virtual int GetMouseY() const = 0;
        virtual bool IsGamepadButtonDown(int aGamepad, EControllerButton aButton) const = 0;
        virtual int GetGamepadAxisX(int aGamePad, int aStick) const = 0;
        virtual int GetGamepadAxisY(int aGamePad, int aStick) const = 0;
        virtual bool IsTriggerDown(int aGamePad, int aTrigger) = 0;
    };
}

#endif
