#ifndef LEVELTWO_H
#define LEVELTWO_H

#include <GameState.h>

class LevelTwo : public bart::GameState
{
public:
	virtual ~LevelTwo() = default;
	void Load() override;
};


#endif