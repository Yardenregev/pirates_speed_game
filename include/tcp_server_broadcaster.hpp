#pragma once
#include <vector>
#include "tcp_component.hpp"

namespace pirates_speed
{
class TCPServerBroadcaster :public TCPComponent
{
public:
    TCPServerBroadcaster(int port, const std::string & ip_address);
    int AddClient();
    void RemoveClient(int client_to_remove);
    void SendMessageToAll(const std::string &message);
    void SendMessageToClient(const std::string &message, int client_socket);
    std::string ReceiveMessageFromClient(int client_socket);
    
private:
    std::vector<int> m_clients;
};
    
} // namespace pirates_speed
