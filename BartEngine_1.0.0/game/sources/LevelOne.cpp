#include <LevelOne.h>
#include <Engine.h>
#include <DemoMap.h>
#include <LevelOneMap.h>
#include <Player.h>
#include <Ennemy.h>
#include <OiseauManager.h>

void LevelOne::Load()
{
	//bart::Engine::Instance().GetScene().AddEntity("Ennemy", new Ennemy);
	//bart::Engine::Instance().GetScene().AddEntity("Player", new Player);
	bart::Engine::Instance().GetScene().AddEntity("LevelOne", new LevelOneMap);
}
