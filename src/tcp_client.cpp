#include "../include/tcp_client.hpp"
#include <stdexcept>
#include <cstring>
#include <iostream>

namespace pirates_speed
{

    TCPClient::TCPClient(int port, const std::string & ip_address)
        : TCPComponent(port, ip_address), m_is_connected(false)
    {
        
    }

    void TCPClient::Connect()
    {
        std::cout << "Waiting for commander to add you in" << std::endl;
        if(connect(m_socket, (struct sockaddr *)&m_server_address, sizeof(m_server_address)) < 0)
        {
            throw std::runtime_error("Error connecting to server");
        }
        m_is_connected = true;
    }
    
    std::string TCPClient::ReceiveMessage()
    {
        if (false == m_is_connected)
        {
            return "";
        }
        char buffer[1024] = {0};
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(m_socket, buffer, sizeof(buffer), 0);
        if(-1 == bytes_received)
        {
            throw std::runtime_error("Error receiving message");
        }
        else if (0 == bytes_received)
        {
            m_is_connected = false;
            return "";
        }
        return std::string(buffer);
    }

    bool TCPClient::IsConnected()
    {
        return m_is_connected;
    }
    
} // namespace pirates_speed
