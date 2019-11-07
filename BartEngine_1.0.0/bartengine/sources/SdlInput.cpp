#include <SdlInput.h>
#include <Engine.h>
#include <SDL.h>

bool bart::SdlInput::Initialize()
{
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if (SDL_NumJoysticks() > 0)
    {
        mHasGamepad = true;
        for (int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_Joystick* tjoystick = SDL_JoystickOpen(i);
            if (SDL_JoystickOpen(i))
            {
                mJoysticks.push_back(tjoystick);

                mStickValues.push_back(
                    std::make_pair(new Point(), new Point()));

                mTriggerValues.push_back(
                    std::make_pair(false, false));

                std::vector<bool> tempButtons;
                for (int j = 0; j < SDL_JoystickNumButtons(tjoystick); j++)
                {
                    tempButtons.push_back(false);
                }

                mGamepadButtonStates.push_back(tempButtons);
            }
        }
    }
    else
    {
        mHasGamepad = false;
    }

    return true;
}

void bart::SdlInput::Clean()
{
    const int tStickValueCnt = static_cast<int>(mStickValues.size());
    for (int i = 0; i < tStickValueCnt; i++)
    {
        delete mStickValues[i].first;
        delete mStickValues[i].second;
    }

    const int tJoystickCnt = static_cast<int>(mJoysticks.size());
    for (int i = 0; i < tJoystickCnt; i++)
    {
        SDL_JoystickClose(mJoysticks[i]);
    }
}

void bart::SdlInput::PoolEvents()
{
    SDL_Event tEvent;
    while (SDL_PollEvent(&tEvent) > 0)
    {
        switch (tEvent.type)
        {
        case SDL_QUIT:
            Engine::Instance().Stop();
            break;

        case SDL_MOUSEMOTION:
            mMouseX = tEvent.motion.x;
            mMouseY = tEvent.motion.y;
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch (tEvent.button.button)
            {
            case SDL_BUTTON_LEFT:
                mMouseState[LEFT] = true;
                break;

            case SDL_BUTTON_RIGHT:
                mMouseState[RIGHT] = true;
                break;

            case SDL_BUTTON_MIDDLE:
                mMouseState[MIDDLE] = true;
                break;
            default:
                break;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            switch (tEvent.button.button)
            {
            case SDL_BUTTON_LEFT:
                mMouseState[LEFT] = false;
                break;

            case SDL_BUTTON_RIGHT:
                mMouseState[RIGHT] = false;
                break;

            case SDL_BUTTON_MIDDLE:
                mMouseState[MIDDLE] = false;
                break;
            default:
                break;
            }
            break;

        case SDL_JOYAXISMOTION:
            UpdateGamepadAxis(&tEvent.jaxis);
            UpdateTriggerAxis(&tEvent.jaxis);
            break;

        case SDL_JOYBUTTONDOWN:
            UpdateGamepadButton(tEvent.jaxis.which, tEvent.jbutton.button, true);
            break;

        case SDL_JOYBUTTONUP:
            UpdateGamepadButton(tEvent.jaxis.which, tEvent.jbutton.button, false);
            break;

        case SDL_JOYHATMOTION:
            switch (tEvent.jhat.value)
            {
            case SDL_HAT_UP:
                mDPadState[0] = true;
                break;

            case SDL_HAT_LEFT:
                mDPadState[2] = true;
                break;

            case SDL_HAT_RIGHT:
                mDPadState[3] = true;
                break;

            case SDL_HAT_DOWN:
                mDPadState[1] = true;
                break;

            case SDL_HAT_LEFTUP:
                mDPadState[0] = true;
                mDPadState[2] = true;
                break;

            case SDL_HAT_RIGHTUP:
                mDPadState[0] = true;
                mDPadState[3] = true;
                break;

            case SDL_HAT_LEFTDOWN:
                mDPadState[1] = true;
                mDPadState[2] = true;
                break;

            case SDL_HAT_RIGHTDOWN:
                mDPadState[1] = true;
                mDPadState[3] = true;
                break;

            default:
                mDPadState[0] = false;
                mDPadState[1] = false;
                mDPadState[2] = false;
                mDPadState[3] = false;
                break;
            }

            break;

        case SDL_KEYDOWN:
            m_KeyStates = SDL_GetKeyboardState(nullptr);
            break;

        case SDL_KEYUP:
            m_KeyStates = SDL_GetKeyboardState(nullptr);
            break;

        default:
            break;
        }
    }
}

bool bart::SdlInput::IsKeyDown(const EKeys aKey)
{
    if (m_KeyStates != nullptr)
    {
        if (m_KeyStates[aKey] == 1)
        {
            return true;
        }
    }

    return false;
}

bool bart::SdlInput::IsMouseButtonDown(EMouseButton aButton)
{
    return mMouseState[aButton];
}

int bart::SdlInput::GetMouseX() const
{
    return mMouseX;
}

int bart::SdlInput::GetMouseY() const
{
    return mMouseY;
}

bool bart::SdlInput::IsGamepadButtonDown(int aGamepad, EControllerButton aButton) const
{
    if (mHasGamepad)
    {
        if (aButton < DPAD_UP)
        {
            return mGamepadButtonStates[aGamepad][aButton];
        }

        //TODO: Needs to add aGamePad here.
        return mDPadState[aButton - DPAD_UP];
    }

    return false;
}

int bart::SdlInput::GetGamepadAxisX(int aGamePad, int aStick) const
{
    if (mHasGamepad)
    {
        if (!mStickValues.empty())
        {
            if (aStick == 1)
            {
                return static_cast<int>(mStickValues[aGamePad].first->X);
            }

            if (aStick == 2)
            {
                return static_cast<int>(mStickValues[aGamePad].second->X);
            }
        }
    }

    return 0;
}

int bart::SdlInput::GetGamepadAxisY(int aGamePad, int aStick) const
{
    if (mHasGamepad)
    {
        if (!mStickValues.empty())
        {
            if (aStick == 1)
            {
                return static_cast<int>(mStickValues[aGamePad].first->Y);
            }

            if (aStick == 2)
            {
                return static_cast<int>(mStickValues[aGamePad].second->Y);
            }
        }
    }

    return 0;
}

bool bart::SdlInput::IsTriggerDown(int aGamePad, int aTrigger)
{
    if (mHasGamepad)
    {
        if (!mTriggerValues.empty())
        {
            if (aTrigger == 1)
            {
                return mTriggerValues[aGamePad].first;
            }

            if (aTrigger == 2)
            {
                return mTriggerValues[aGamePad].second;
            }
        }
    }

    return false;
}

void bart::SdlInput::UpdateGamepadButton(int aGamepad, int aButton, bool aDown)
{
    if (mHasGamepad)
    {
        mGamepadButtonStates[aGamepad][aButton] = aDown;
    }
}

void bart::SdlInput::UpdateGamepadAxis(SDL_JoyAxisEvent* aEvent)
{
    if (mHasGamepad)
    {
        int tGamePad = (*aEvent).which;
        int tValue = (*aEvent).value;
        int tAxis = (*aEvent).axis;

        float tDirection = 0;

        if (tValue > mStickDeadZone)
        {
            tDirection = static_cast<float>(tValue);
        }
        else if (tValue < -mStickDeadZone)
        {
            tDirection = static_cast<float>(tValue);
        }

        if (tAxis == 0)
        {
            mStickValues[tGamePad].first->X = static_cast<int>(tDirection);
        }

        if (tAxis == 1)
        {
            mStickValues[tGamePad].first->Y = static_cast<int>(tDirection);
        }

        if (tAxis == 3)
        {
            mStickValues[tGamePad].second->X = static_cast<int>(tDirection);
        }

        if (tAxis == 4)
        {
            mStickValues[tGamePad].second->Y = static_cast<int>(tDirection);
        }
    }
}

void bart::SdlInput::UpdateTriggerAxis(SDL_JoyAxisEvent* aEvent)
{
    if (mHasGamepad)
    {
        int tGamePad = (*aEvent).which;
        int tValue = (*aEvent).value;
        int tAxis = (*aEvent).axis;

        if (tAxis == 2)
        {
            mTriggerValues[tGamePad].first = (tValue > mTriggerDeadZone);
        }

        if (tAxis == 5)
        {
            mTriggerValues[tGamePad].second = (tValue > mTriggerDeadZone);
        }
    }
}
