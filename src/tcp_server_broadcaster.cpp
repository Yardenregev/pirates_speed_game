#include "../include/tcp_server_broadcaster.hpp"
#include <stdexcept>
#include <iostream>/*std cout cin*/
#include <cstring>
namespace pirates_speed
{

    TCPServerBroadcaster::TCPServerBroadcaster( int port, const std::string & ip_address)
        : TCPComponent(port, ip_address),
            m_clients()
    {
        if(bind(m_socket, (struct sockaddr *)&m_server_address, sizeof(m_server_address)) < 0)
        {
            throw std::runtime_error("Error binding socket");
        }
    }


    int TCPServerBroadcaster::AddClient()
    {
        if(listen(GetSocket(), 1) == -1)
        {
            throw std::runtime_error("Error listening for connections");
        }

        socklen_t len = sizeof(m_server_address);
        int client_socket = accept(GetSocket(), (struct sockaddr *)&m_server_address, &len);
        if(client_socket == -1)
        {
            throw std::runtime_error("Error accepting connection");
        }
        m_clients.push_back(client_socket);
        return client_socket;
    }

    void TCPServerBroadcaster::SendMessageToAll(const std::string &message)
    {
        for(auto client : m_clients)
        {
            if(send(client, message.c_str(), message.size(), 0) == -1)
            {
                continue;
            }
        }
    }

    void TCPServerBroadcaster::SendMessageToClient(const std::string &message, int client_socket)
    {
        if(send(client_socket, message.c_str(), message.size(), 0) == -1)
        {
            throw std::runtime_error("Error sending message to client");
        }
    }

    std::string TCPServerBroadcaster::ReceiveMessageFromClient(int client_socket)
    {
        char buffer[1024] = {0};
        memset(buffer, 0, sizeof(buffer));
        if(recv(client_socket, buffer, 1024, 0) == -1)
        {
            throw std::runtime_error("Error recieving message from client");
        }
        return buffer;
    }


    // char *TCPServerBroadcaster::ReciveMessageFromLastClient()
    // {
    //     char *buffer = new char[1024];
    //     if(recv(m_clients.back(), buffer, 1024, 0) == -1)
    //     {
    //         throw std::runtime_error("Error recieving message");
    //     }
    //     return buffer;
    // }

    // void TCPServerBroadcaster::SendMessageToLastClient(const std::string &message)
    // {
    //     if(send(m_clients.back(), message.c_str(), message.size(), 0) == -1)
    //     {
    //         throw std::runtime_error("Error sending message");
    //     }
    // }
    
} // namespace pirates_speed
    
