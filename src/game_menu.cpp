#include "../include/game_menu.hpp"
#include <iostream>/*std cout cin*/
#include <thread>

namespace pirates_speed
{


GameMenu::GameMenu()
: m_set_up_game(false),
  m_game(nullptr),
  m_captain_count(0)
  {}


void GameMenu::ShowMenu()
{
    std::cout << "1. Set up game" << std::endl;
    std::cout << "2. Add captain" << std::endl;
    std::cout << "3. Start game" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void GameMenu::TakeChoice()
{
    int choice;
    while(1)
    {
    std::cout << "Enter main menu choice: ";
    std::cin >> choice;
        switch(choice)
        {
            case 1:
                SetUpGame();
                break;
            case 2:
                AddCaptain();
                break;
            case 3:
                StartGame();
                return;
            case 4:
                return;
            default:
                std::cout << "Invalid choice" << std::endl;
                break;
        }
    }

}

void GameMenu::SetUpGame()
{
    std::string commander_name;
    int commander_port;
    std::string commander_ip_address;
    std::cout << "Set up game" << std::endl;
    std::cout << "Enter commander name: ";
    std::cin >> commander_name;
    std::cout << "Enter commander port: ";
    std::cin >> commander_port;
    std::cout << "Enter commander ip address: ";
    std::cin >> commander_ip_address;

    if(commander_name.empty() || commander_ip_address.empty() || commander_port == 0)
    {
        std::cout << "Invalid commander name, ip address or port" << std::endl;
        return;
    }

    m_game = std::make_shared<Game>(commander_name, commander_port, commander_ip_address);
    m_set_up_game = true;

}


void GameMenu::AddCaptain()
{
    if (!m_set_up_game)
    {
        std::cout << "Set up game first" << std::endl;
        return;
    }

    if(m_captain_count >= std::thread::hardware_concurrency())
    {
        std::cout << "Maximum number of captains reached" << std::endl;
        return;
    }

    m_game->AddCaptain();
    m_captain_count++;
}

void GameMenu::StartGame()
{
    if (!m_set_up_game || m_captain_count == 0)
    {
        std::cout << "Set up game and add captains first" << std::endl;
        return;
    }
    m_game->StartGame();
}


} // namespace pirates_speed