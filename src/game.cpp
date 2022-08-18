#include "../include/game.hpp"
#include "../include/design_patterns/singleton.hpp"
#include <iostream>/*std cout cin*/
#include "../include/pirate_types/pirate_types.hpp"

namespace pirates_speed
{

    Game::Game()
    : m_commander(),
      m_captains(),
      m_winner(nullptr),
      m_game_pirate_inventory()
    {
        m_game_pirate_inventory.Add("Cleaner", std::dynamic_pointer_cast<CrewPirate>(std::make_shared<Cleaner>("Skippy")));
        m_game_pirate_inventory.Add("Cook", std::dynamic_pointer_cast<CrewPirate>(std::make_shared<Cook>("Salty")));
        m_game_pirate_inventory.Add("Sailor", std::dynamic_pointer_cast<CrewPirate>(std::make_shared<Sailor>("Smith")));
        m_game_pirate_inventory.Add("Looter", std::dynamic_pointer_cast<CrewPirate>(std::make_shared<Looter>("Lucky")));
        m_game_pirate_inventory.Add("Defender", std::dynamic_pointer_cast<CrewPirate>(std::make_shared<Defender>("Black Beard")));
    }

    Game::~Game()
    {
    }
    
    Game& Game::GetInstance()
    {
        return Singleton<Game>::GetInstance();
    }

    void Game::AddCaptain(const std::string & name, size_t num_of_crew_pirates)
    {
        m_captains.push_back(std::make_shared<Captain>(m_commander, name,
                                                       m_game_pirate_inventory, num_of_crew_pirates));
    }

    void Game::StartGame()
    {
        std::cout << "Game started" << std::endl;
        while (!CheckIfGameIsOver())
        {
            std::string given_command;
            std::cout << "Enter command: " << std::endl;
            std::cin >> given_command;
            m_commander.ShoutCommand(given_command);
        }

        PrintGameOver();
    }

    bool Game::CheckIfGameIsOver()
    {
        for (auto & captain : m_captains)
        {
            if (captain->IsWinner())
            {
                m_winner = captain;
                return true;
            }
        }
        return false;
    }

    void Game::PrintGameOver()
    {
        std::cout << "Game over! The winner is: " << m_winner->GetName() << std::endl;
    }

    void Game::AddPirateToGameInventory(const std::string &role, std::shared_ptr<CrewPirate> pirate)
    {
        m_game_pirate_inventory.Add(role, pirate);
    }



} // namespace pirates_speed