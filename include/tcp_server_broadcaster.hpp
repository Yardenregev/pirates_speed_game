#pragma once
#include <vector>
#include "tcp_component.hpp"

namespace pirates_speed
{
class TCPServerBroadcaster :public TCPComponent
{
public:
    TCPServerBroadcaster(int port, const std::string & ip_address);
    void AddClient();
    void SendMessageToAll(const std::string &message);
    void SendMessageToLastClient(const std::string &message);
    char *ReciveMessageFromLastClient();
private:
    std::vector<int> m_clients;
};
    
} // namespace pirates_speed
