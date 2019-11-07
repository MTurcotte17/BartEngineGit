#include <TestMaps.h>
#include <Engine.h>
#include <DemoMap.h>

void TestMap::Load()
{
    bart::Engine::Instance().GetScene().AddEntity("DemoMap", new DemoMap());
}
