#include <LevelOne.h>
#include <Engine.h>
#include <DemoMap.h>
#include <LevelOneMap.h>
#include <Player.h>
#include <Ennemy.h>

void LevelOne::Load()
{
	OiseauManager::Instance().SetCurrentLevel(1);
	bart::Engine::Instance().GetScene().AddEntity("LevelOne", new LevelOneMap);
}
