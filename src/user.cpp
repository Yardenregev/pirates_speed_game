#include <iostream>
#include "../include/user.hpp"
#include "../include/exceptions.hpp"
#include "../include/messages.hpp"
#include "../include/utils.hpp"

namespace pirates_speed
{
    User::User(const std::string & name, size_t num_of_pirates, const std::string & ip_address, int port)
        : m_tcp_client(port, ip_address), m_name(name),m_num_of_pirates(num_of_pirates)
    {
    }

    User::RegistrationStatus User::Register()
    {
        try{
            m_tcp_client.Connect();
            SendUserDetails();
            return IsConnectedToGame();
        }
        catch (std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }
        return REGISTRATION_FAILURE;
    }

    void User::SendMessage(const std::string &message)
    {
        std::string new_message = m_name + "-" + message;
        m_tcp_client.SendMessage(new_message);
    }

    std::string User::ReceiveMessage()
    {
        std::string message = m_tcp_client.ReceiveMessage();
        if (!m_tcp_client.IsConnected())
        {
            throw ConnectionWithCommanderException();
        }
        return message;
    }


    void User::SendUserDetails()
    {
        std::string message = m_name + "-" + std::to_string(m_num_of_pirates);
        m_tcp_client.SendMessage(message);
    }


    void User::ShowReply()
    {
        std::cout << ReceiveMessage() << std::endl;
    }

    bool User::IsGameOver(const std::string &message)
    {
        std::string end_game = message.substr(0, message.find("-"));
        return end_game == "Game over";
    }
    

    void User::StartGame()
    {
        try
        {
            std::string inventory = ReceiveMessage();
            std::string command = "";
            std::string choice;
            while(!IsGameOver(inventory))
            {
                SendMessage(Messages::start_round);
                std::cout << inventory << std::endl;
                std::cout << "Waiting for command from commander..." << std::endl;
                command = ReceiveMessage();
                std::cout << "Commander: " << command << std::endl;
                Utils::ClearInputBuffer();
                std::getline(std::cin, choice);
                SendMessage(choice);
                std::string reply = ReceiveMessage();
                std::cout << "Reply: " << reply << std::endl;
                SendMessage(Messages::end_round);
                inventory = ReceiveMessage();
            }

            std::cout << inventory << std::endl;
        }
        catch (ConnectionWithCommanderException &e)
        {
            std::cerr << e.what() << std::endl;
            return;
        }
    }


    User::RegistrationStatus User::IsConnectedToGame()
    {
        try
        {
            std::string connection_status = ReceiveMessage();
            if (0 == connection_status.compare(Messages::connected))
            {
                return REGISTRATION_SUCCESS;
            }
            else if (0 == connection_status.compare(Messages::name_taken))
            {
                std::cout << "Name " << m_name << " already taken"<< std::endl;
            }
            return REGISTRATION_FAILURE;
        }
        catch (ConnectionWithCommanderException &e)
        {
            std::cerr << e.what() << std::endl;
            return REGISTRATION_FAILURE;
        }
    }
} // namespace pirates_speed