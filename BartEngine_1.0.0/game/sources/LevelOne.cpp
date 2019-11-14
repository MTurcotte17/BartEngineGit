#include <LevelOne.h>
#include <Engine.h>
#include <DemoMap.h>
#include <LevelOneMap.h>
#include <Player.h>

void LevelOne::Load()
{
	bart::Engine::Instance().GetScene().AddEntity("Player", new Player);
	bart::Engine::Instance().GetScene().AddEntity("LevelOne", new LevelOneMap);
}
