#include <NullInput.h>

bool bart::NullInput::Initialize()
{
    return true;
}

void bart::NullInput::Clean()
{
}

void bart::NullInput::PoolEvents()
{
}

bool bart::NullInput::IsKeyDown(EKeys aKey)
{
    return false;
}

bool bart::NullInput::IsMouseButtonDown(EMouseButton aButton)
{
    return false;
}

int bart::NullInput::GetMouseX() const
{
    return 0;
}

int bart::NullInput::GetMouseY() const
{
    return 0;
}

bool bart::NullInput::IsGamepadButtonDown(int aGamepad, EControllerButton aButton) const
{
    return false;
}

int bart::NullInput::GetGamepadAxisX(int aGamePad, int aStick) const
{
    return 0;
}

int bart::NullInput::GetGamepadAxisY(int aGamePad, int aStick) const
{
    return 0;
}

bool bart::NullInput::IsTriggerDown(int aGamePad, int aTrigger)
{
    return false;
}
