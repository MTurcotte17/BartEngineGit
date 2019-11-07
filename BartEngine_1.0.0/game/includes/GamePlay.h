#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <GameState.h>

class GamePlay : public bart::GameState
{
public:
    virtual ~GamePlay() = default;
    void Load() override;
};

#endif