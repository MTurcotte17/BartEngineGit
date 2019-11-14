#ifndef LEVELONE_H
#define LEVELONE_H

#include <GameState.h>

class LevelOne : public bart::GameState
{
public:
	virtual ~LevelOne() = default;
	void Load() override;
};


#endif
