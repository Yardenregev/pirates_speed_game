#include "../include/game.hpp"
#include "../include/design_patterns/singleton.hpp"
#include <iostream>/*std cout cin*/
#include "../include/pirate_types/pirate_types.hpp"
#include <memory>



namespace pirates_speed
{

    Game::Game(const std::string & commander_name, int port, const std::string & ip_address)
    : m_commander(new Commander(commander_name, port, ip_address)),
      m_captains(),
      m_winner(nullptr),
      m_game_pirate_inventory(),
      m_mutex(),
      m_condition_variable()
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

    // void Game::ConnectCommanderToCaptain()
    // {
    //     m_condition_variable.notify_one();
    //     m_commander->AddCaptain();
    // }

    // void Game::ConnectCaptainToCommander(std::shared_ptr<Captain> &captain)
    // {
    //     std::unique_lock<std::mutex> lock(m_mutex);
    //     m_condition_variable.wait(lock);
    //     captain->ConnectCommander();
    // }

    // void Game::ConnectCommanderAndCaptain(std::shared_ptr<Captain> &captain)
    // {
    //     std::thread thread(&Game::ConnectCommanderToCaptain, this);
    //     ConnectCaptainToCommander(captain);
    //     thread.join();
    // }

    void Game::RegisterCaptain()
    {
        std::string name;
        int port;
        std::string ip_address;
        size_t num_of_crew_pirates;
        std::cout << "Enter captain name: ";
        std::cin >> name;
        std::cout << "Enter captain port: ";
        std::cin >> port;
        std::cout << "Enter captain ip address: ";
        std::cin >> ip_address;
        std::cout << "Enter captain number of crew pirates: ";
        std::cin >> num_of_crew_pirates;

        if(name.empty() || ip_address.empty() || port == 0 || num_of_crew_pirates == 0)
        {
            std::cout << "Invalid captain name, ip address or port" << std::endl;
            return;
        }

        std::shared_ptr<Captain> captain = std::make_shared<Captain>(name, 
                m_game_pirate_inventory, ip_address, port, num_of_crew_pirates);
        
        
        m_commander->AddCaptain();
        m_captains.push_back(captain);
        std::cout << "Captain " << name << " registered" << std::endl;
    }   



    void Game::AddCaptain()
    {
        RegisterCaptain();
    }

    // void Game::AddCaptain(std::shared_ptr<Captain> captain)
    // {
    //     std::thread thread(&Commander::AddCaptain, m_commander, captain);
        
    //     thread.join();
    // }

    void Game::StartGame()
    {
        std::cout << "Game started" << std::endl;
        while (!CheckIfGameIsOver())
        {
            std::string given_command;
            std::cout << "Enter command: " << std::endl;
            std::cin >> given_command;
            // for (auto &captain : m_captains)
            // {
            //     captain->RecieveMessage();
            // }
            m_commander->ShoutCommand(given_command);
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