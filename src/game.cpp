#include <iostream>/*std cout cin*/
#include <memory>
#include <vector>
#include <unordered_set>
#include "../include/game.hpp"
#include "../include/pirate_types/pirate_types.hpp"
#include "../include/threadpool.hpp"
#include "../include/server.hpp"
#include "../include/messages.hpp"
#include "../include/utils.hpp"


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




    Game::GameStatus Game::AddCaptain()
    {
        auto captain_details = m_server.AddCaptain();
        if (captain_details.first == "")
        {
            return GAME_FAILURE;
        }
        std::shared_ptr<Captain> captain = std::make_shared<Captain>(captain_details.first,m_game_pirate_inventory ,captain_details.second);
        if(m_captains.find(captain->GetName()) == m_captains.end())
        {
            m_captains[captain->GetName()] = captain;
            std::cout << "Captain " << captain->GetName() << " registered" << std::endl;
            if (Server::MESSAGE_SENT == m_server.SendMessageToCaptain(captain->GetName(),Messages::connected))
            {
                return GAME_SUCCESS;
            }
        }
        return GAME_FAILURE;
    }


    void Game::StartGame()
    {
        std::cout << "Game started" << std::endl;
        while (!CheckIfGameIsOver())
        {
            SendInventoriesToAllCaptains();
            ReceiveFromAll();

            std::string given_command;
            std::cout << "Enter command: " << std::endl;
            Utils::ClearInputBuffer();
            std::getline(std::cin, given_command);
            m_server.ShoutCommand(given_command);   
            m_server.QueueAnswers();
            HandleAnswers(given_command);
            m_server.ClearAnswerQueue();
            ReceiveFromAll();
        }

        SendGameOver();
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
        std::vector<std::string> captains_to_remove;
        for (auto &captain : m_captains)
        {
            std::string inventory_string = captain.second->GetInventoryString();
            if (Server::MESSAGE_CAPTAINNOTFOUND ==  m_server.SendMessageToCaptain(captain.second->GetName(), inventory_string))
            {
               captains_to_remove.push_back(captain.first);
            }
            else
            {
                std::cout << "Sent inventory to Captain " << captain.second->GetName() << std::endl;
            }
        }
        for (auto &captain_to_remove : captains_to_remove)
        {
            std::cout << "Removing captain "<< captain_to_remove << std::endl;
            m_captains.erase(captain_to_remove);
        }
    }

    void Game::SendGameOver()
    {
        std::string game_over_msg = "Game over-";
        game_over_msg += "winner is " + m_winner->GetName();
        game_over_msg += "\n";
        m_server.SendMessageToAll(game_over_msg);
    }

    void Game::AddPirateToGameInventory(const std::string &role, std::shared_ptr<CrewPirate> pirate)
    {
        m_game_pirate_inventory.Add(role, pirate);
    }

    void Game::HandleAnswers(const std::string &command)
    {
        std::shared_ptr<Answer> answer;
        m_server.GetAnswer(answer);
        std::string correct_captain_name = "";
        size_t answer_count = 1;
        std::unordered_set<std::string> answered_captains;
        while(answer->GetPriority() != Priority::END_ROUND)
        {
            bool correct = MakeCaptainHandleAnswer(answer->GetCaptainName(), answer, command);
            answered_captains.insert(answer->GetCaptainName());
            if(correct)
            {
                m_server.EndRound();
                correct_captain_name = answer->GetCaptainName();
                m_server.SendMessageToCaptain(answer->GetCaptainName(), Messages::correct_answer);
                break;
            }

            else
            {
                m_server.SendMessageToCaptain(answer->GetCaptainName(), Messages::wrong_answer);
            }
            
            if (answer_count == m_captains.size())
            {
                break;
            }

            m_server.GetAnswer(answer);
            answer_count++;
        }

        for(auto &captain : m_captains)
        {
            if(answered_captains.find(captain.second->GetName()) == answered_captains.end())
            {
                m_server.SendMessageToCaptain(captain.second->GetName(), Messages::too_slow_answer);
            }
        }

        // AddPirateForAllButCorrectCaptain(correct_captain_name); // feature not working all the time

        m_server.EndRound();
    }


    void Game::AddPirateForAllButCorrectCaptain(const std::string &correct_captain_name)
    {
        for (auto &captain : m_captains)
        {
            if(captain.second->GetName() != correct_captain_name)
            {
                captain.second->AddRandomPirate();
            }
        }
    }

    bool Game::MakeCaptainHandleAnswer(const std::string &captain_name, std::shared_ptr<Answer> answer, const std::string &command)
    {
       if(m_server.IsAnswered())
       {
            return false;
       }

       auto captain = m_captains.find(captain_name);
       if(captain == m_captains.end())
       {
           std::cout << "Captain not found" << std::endl;
           return false;
       }
       else
       {
           return captain->second->HandleAnswer(answer, command);
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

    void Game::ReceiveFromAll()
    {
        m_server.ReceiveFromAll();   
    }

} // namespace pirates_speed