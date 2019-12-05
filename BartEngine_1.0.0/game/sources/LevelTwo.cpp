#include <LevelTwo.h>
#include <Engine.h>
#include <DemoMap.h>
#include <LevelTwoMap.h>
#include <Player.h>
#include <Ennemy.h>

void LevelTwo::Load()
{
	OiseauManager::Instance().SetCurrentLevel(2);
	bart::Engine::Instance().GetScene().AddEntity("LevelTwo", new LevelTwoMap);
}
