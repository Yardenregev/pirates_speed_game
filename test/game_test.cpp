#include "../include/game.hpp"

using namespace pirates_speed;

void TestGame()
{
    Game& game = Game::GetInstance();
    game.AddCaptain("yarden", 5);
    game.AddCaptain("georgi", 5);

    game.StartGame();
}

int main ()
{
    TestGame();




    return 0;
}
