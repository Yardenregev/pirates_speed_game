#include "../include/game.hpp"
#include "../include/design_patterns/singleton.hpp"
#include <iostream>/*std cout cin*/

namespace pirates_speed
{
    Game& Game::GetInstance()
    {
        return Singleton<Game>::GetInstance();
    }


    void Game::StartGame()
    {
        std::cout << "Game is starting" << std::endl;
    }

    void Game::EndGame()
    {
        std::cout << "Game is ending" << std::endl;
    }

} // namespace pirates_speed