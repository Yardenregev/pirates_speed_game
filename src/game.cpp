#include "../include/game.hpp"
#include "../include/singleton.hpp"
#include <iostream>/*std cout cin*/
namespace pirates_speed
{
    Game& Game::GetInstance()
    {
        return Singleton<Game>::GetInstance();
    }

    Game::~Game()
    {
        std::cout << "Game is over" << std::endl;
    }

    void Game::StartGame()
    {
        std::cout << "Game is starting" << std::endl;
    }

} // namespace pirates_speed