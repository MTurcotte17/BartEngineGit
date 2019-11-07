#ifndef MAINMENU_H
#define MAINMENU_H

#include <GameState.h>

class MainMenu : public bart::GameState
{
public:
    virtual ~MainMenu() = default;
    void Load() override;
};

#endif