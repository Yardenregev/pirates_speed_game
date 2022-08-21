#include "../include/tcp_component.hpp"
#include <sys/types.h>
#include <stdexcept>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

namespace pirates_speed
{

    TCPComponent::TCPComponent(int port, const std::string & ip_address)
         : m_port(port),
          m_ip_address(ip_address),
          m_server_address(),
          m_socket(0)
          
    {
        m_socket = socket(AF_INET,SOCK_STREAM,0);
        if (m_socket < 0)
        {
            throw std::runtime_error("Error creating socket");
        }

        memset(&m_server_address, 0, sizeof(m_server_address));

        m_server_address.sin_family = AF_INET;
        m_server_address.sin_port = htons(m_port);
        inet_pton(AF_INET, m_ip_address.c_str(), &m_server_address.sin_addr);

    }

    int TCPComponent::GetSocket() const
    {
        return m_socket;
    }

    

    void TCPComponent::SendMessage(const std::string &message)
    {
        int bytes_sent = send(m_socket, message.c_str(), message.size(), 0);
        if(bytes_sent == -1)
        {
            throw std::runtime_error("Error sending message");
        }
    }

    TCPComponent::~TCPComponent()
    {
        close(m_socket);
    }
    
} // namespace pirates_speed
