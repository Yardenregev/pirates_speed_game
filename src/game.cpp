#include "../include/game.hpp"
#include "../include/design_patterns/singleton.hpp"
#include <iostream>/*std cout cin*/
#include "../include/pirate_types/pirate_types.hpp"
#include <memory>



namespace pirates_speed
{

    Game::Game(const std::string & commander_name, int port, const std::string & ip_address)
    : m_server(port, ip_address),
      m_commander_name(commander_name),
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



    void Game::RegisterCaptain()
    {
        // int port;
        // std::string ip_address;
        // size_t num_of_crew_pirates;
        // std::cout << "Enter captain name: ";
        // std::cin >> name;
        // std::cout << "Enter captain port: ";
        // std::cin >> port;
        // std::cout << "Enter captain ip address: ";
        // std::cin >> ip_address;
        // std::cout << "Enter captain number of crew pirates: ";
        // std::cin >> num_of_crew_pirates;

        // if(name.empty() || ip_address.empty() || port == 0 || num_of_crew_pirates == 0)
        // {
        //     std::cout << "Invalid captain name, ip address or port" << std::endl;
        //     return;
        // }

        
        auto captain_details = m_server.AddCaptain();
        std::shared_ptr<Captain> captain = std::make_shared<Captain>(captain_details.first,m_game_pirate_inventory ,captain_details.second);
        m_captains[captain->GetName()] = captain;
        std::cout << "Captain " << captain->GetName() << " registered" << std::endl;
    }   



    void Game::AddCaptain()
    {
        RegisterCaptain();
    }


    void Game::StartGame()
    {
        std::cout << "Game started" << std::endl;
        while (!CheckIfGameIsOver())
        {
            SendInventoriesToAllCaptains();
            std::string given_command;
            std::cout << "Enter command: " << std::endl;
            std::cin >> given_command;
            m_server.ShoutCommand(given_command);   
            m_server.QueueAnswers();
            HandleAnswers(given_command);
        }

        PrintGameOver();
    }

    bool Game::CheckIfGameIsOver() // check later for more efficiant solution
    {
        for (auto &captain : m_captains)
        {
            if (captain.second->IsWinner())
            {
                m_winner = captain.second;
                m_server.EndGame();
                return true;
            }
        }
        return false;
    }

    void Game::SendInventoriesToAllCaptains()
    {
        for (auto &captain : m_captains)
        {
            std::string inventory_string = captain.second->GetInventoryString();
            m_server.SendMessageToCaptain(captain.second->GetName(), inventory_string);
        }
    }

    void Game::PrintGameOver()
    {
        std::cout << "Game over! The winner is: " << m_winner->GetName() << std::endl;
    }

    void Game::AddPirateToGameInventory(const std::string &role, std::shared_ptr<CrewPirate> pirate)
    {
        m_game_pirate_inventory.Add(role, pirate);
    }

    void Game::HandleAnswers(const std::string &command)
    {
        std::shared_ptr<Answer> answer;
        m_server.GetAnswer(answer);
        std::cout << "Answer "<< answer->GetAnswer() << std::endl;
        bool correct = MakeCaptainHandleAnswer(answer->GetCaptainName(), answer, command);
        if(correct)
        {
            m_server.EndRound();
        }

        else
        {
            m_server.SendMessageToCaptain(answer->GetCaptainName(), "Wrong answer\n");
        }
    }

    bool Game::MakeCaptainHandleAnswer(const std::string &captain_name, std::shared_ptr<Answer> answer, const std::string &command)
    {
       auto captain = m_captains[captain_name];
       if(captain == nullptr)
       {
           std::cout << "Captain not found" << std::endl;
           return false;
       }
       else
       {
           return captain->HandleAnswer(answer, command);
       }

    }

    std::string Game::GetCaptainInventory(const std::string &captain_name)
    {
        auto captain = m_captains[captain_name];
        if(captain == nullptr)
        {
            throw std::runtime_error("Captain not found");
        }
        else
        {
            return captain->GetInventoryString();
        }
    }



} // namespace pirates_speed