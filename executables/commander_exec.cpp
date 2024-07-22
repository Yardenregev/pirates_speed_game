#include "../include/game_menu.hpp"

using namespace pirates_speed;


GameMenu::SetupStatus TestGame()
{
    GameMenu game_menu;
    return game_menu.TakeChoice();
}

int main ()
{
    return TestGame();
}
