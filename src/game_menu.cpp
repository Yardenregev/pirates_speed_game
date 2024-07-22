#include "../include/game_menu.hpp"
#include <iostream>/*std cout cin*/
#include <thread>
#include "../include/default_values.hpp"

namespace pirates_speed
{
enum MenuChoices{
    CHOICE_SETUPGAME = 1,
    CHOICE_ADDCAPTAIN,
    CHOICE_STARTGAME,
    CHOICE_EXIT
};

GameMenu::GameMenu()
: m_set_up_game(false),
  m_game(nullptr),
  m_captain_count(0)
  {}


void GameMenu::ShowMenu()
{
    std::cout << CHOICE_SETUPGAME <<". Set up game" << std::endl;
    std::cout << CHOICE_ADDCAPTAIN <<". Add captain" << std::endl;
    std::cout << CHOICE_STARTGAME <<". Start game" << std::endl;
    std::cout << CHOICE_EXIT <<". Exit" << std::endl;
}

GameMenu::SetupStatus GameMenu::TakeChoice()
{
    int choice;
    SetupStatus stat = SETUP_SUCCESS;
    while(1)
    {
    ShowMenu();
    std::cout << "Enter main menu choice: ";
    std::cin >> choice;
    
        switch(choice)
        {
            case CHOICE_SETUPGAME:
                stat = SetUpGame();
                if (SETUP_FAILURE == stat)
                {
                    return SETUP_FAILURE;
                }
                break;
            case CHOICE_ADDCAPTAIN:
                AddCaptain();
                break;
            case CHOICE_STARTGAME:
                stat = StartGame();
                if (SETUP_FAILURE == stat)
                {
                    break;
                }
                else
                {
                    return stat;
                }
            case CHOICE_EXIT:
                return SETUP_SUCCESS;
            default:
                std::cout << "Invalid choice" << std::endl;
                break;
        }
    }

}

GameMenu::SetupStatus GameMenu::SetUpGame()
{
    if (m_set_up_game)
    {
        std::cout << "Game already made" << std::endl;
        return SETUP_SUCCESS;
    }
    std::string commander_name;
    int commander_port;
    std::string commander_ip_address = DefaultValues::getDefaultIP();
    std::cout << "Set up game" << std::endl;
    if (commander_ip_address.empty())
    {
        std::cout << "Could not retreive IP of computer"<<std::endl;
        std::cout << "Enter commander ip address: ";
        std::cin >> commander_ip_address;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (commander_ip_address.empty())
        {
            std::cout << "Invalid ip address" << std::endl;
            return SETUP_FAILURE;
        }
    }
    std::cout << "Enter commander name [" <<DefaultValues::getDefaultCommanderName() << "]: " << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, commander_name);
    if (commander_name.empty())
    {
        commander_name = DefaultValues::getDefaultCommanderName();
    }

    std::cout << "Enter commander port["<< DefaultValues::getDefaultPort() << "]: " << std::endl;
    std::string port_str;
    std::getline(std::cin, port_str);
    try{
        commander_port = std::stoi(port_str);
    }
    catch (...)
    {
        commander_port = DefaultValues::getDefaultPort();
    }
    std::cout << "made game with name " << commander_name
             << ", port " << commander_port << " and ip " 
             << commander_ip_address << std::endl;
    m_game = std::make_shared<Game>(commander_name, commander_port, commander_ip_address);
    m_set_up_game = true;

    return SETUP_SUCCESS;
}


GameMenu::SetupStatus GameMenu::AddCaptain()
{
    if (!m_set_up_game)
    {
        std::cout << "Set up game first" << std::endl;
        return SETUP_FAILURE;
    }

    if(m_captain_count >= std::thread::hardware_concurrency())
    {
        std::cout << "Maximum number of captains reached" << std::endl;
        return SETUP_FAILURE;
    }

    m_game->AddCaptain();
    m_captain_count++;

    return SETUP_SUCCESS;
}

GameMenu::SetupStatus GameMenu::StartGame()
{
    if (!m_set_up_game || m_captain_count == 0)
    {
        std::cout << "Set up game and add captains first" << std::endl;
        return SETUP_FAILURE;
    }
    m_game->StartGame();

    return SETUP_SUCCESS;
}




} // namespace pirates_speed