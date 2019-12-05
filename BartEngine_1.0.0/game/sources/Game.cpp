#include <Engine.h>
#include <MainMenu.h>
#include <GamePlay.h>
#include <TestMaps.h>
#include <LevelOne.h>
#include <LevelTwo.h>

using namespace bart;

#if USE_VLD
#include <vld.h>
#pragma comment(lib, "vld.lib")
#endif

void RegisterGameStates()
{
    Engine::Instance().GetScene().Register("MainMenu", new MainMenu());
    Engine::Instance().GetScene().Register("GamePlay", new GamePlay());
    Engine::Instance().GetScene().Register("TestMap", new TestMap());
	Engine::Instance().GetScene().Register("LevelOne", new LevelOne());
	Engine::Instance().GetScene().Register("LevelTwo", new LevelTwo());

}

int main()
{
    if (Engine::Instance().Initialize("BLOKS", 800, 608))
    {
        RegisterGameStates();

        Engine::Instance().GetScene().Load("MainMenu");
        Engine::Instance().Start();
    }
    return 0;
}
