#include <MainMenu.h>
#include <Engine.h>
#include <MenuScreen.h>
#include <MenuOption.h>

void MainMenu::Load()
{
    Engine::Instance().GetScene().AddEntity("MenuScreen", new MenuScreen());
    Engine::Instance().GetScene().AddEntity("MenuOption", new MenuOption());
    
}
