#include "../include/user.hpp"

#include <iostream>

namespace pirates_speed
{
    User::User(const std::string & name, size_t num_of_pirates, const std::string & ip_address, int port)
        : m_tcp_client(port, ip_address), m_name(name),m_num_of_pirates(num_of_pirates)
    {
    }

    void User::Register()
    {
        m_tcp_client.Connect();
        std::cout << "Connected to server" << std::endl;
        SendUserDetails();
    }

    void User::SendMessage(const std::string &message)
    {
        std::string new_message = m_name + "-" + message;
        m_tcp_client.SendMessage(new_message);
    }

    std::string User::ReceiveMessage()
    {
        return m_tcp_client.ReceiveMessage();
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

    bool User::CheckGameOver(const std::string &message)
    {
        if (message == "end_game")
        {
            std::cout << "Game Over" << std::endl;
            return true;
        }

        return false;
    }
    
} // namespace pirates_speed