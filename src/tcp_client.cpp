#include "../include/tcp_client.hpp"
#include <stdexcept>

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
    
} // namespace pirates_speed
