#include "../include/tcp_client.hpp"
#include <stdexcept>
#include <cstring>

namespace pirates_speed
{

    TCPClient::TCPClient(int port, const std::string & ip_address)
        : TCPComponent(port, ip_address)
    {
        
    }

    void TCPClient::Connect()
    {
        if(connect(m_socket, (struct sockaddr *)&m_server_address, sizeof(m_server_address)) < 0)
        {
            throw std::runtime_error("Error connecting to server");
        }
    }
    std::string TCPClient::ReceiveMessage()
    {
        char buffer[1024] = {0};
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(m_socket, buffer, sizeof(buffer), 0);
        if(bytes_received == -1)
        {
            throw std::runtime_error("Error receiving message");
        }
        return std::string(buffer);
    }
    
} // namespace pirates_speed
