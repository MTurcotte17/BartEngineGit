#include <Engine.h>
#include <MainMenu.h>
#include <GamePlay.h>
#include <TestMaps.h>

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
