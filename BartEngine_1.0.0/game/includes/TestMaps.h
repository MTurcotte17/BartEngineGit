#ifndef TEST_MAPS_H
#define TEST_MAPS_H

#include <GameState.h>

class TestMap : public bart::GameState
{
public:
    virtual ~TestMap() = default;
    void Load() override;
};

#endif