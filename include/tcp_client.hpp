#pragma once
#include "tcp_component.hpp"

namespace pirates_speed
{
class TCPClient : public TCPComponent
{
public:
    TCPClient(int port, const std::string & ip_address);
    std::string ReceiveMessage();
    void Connect();
    bool IsConnected();
private:
    bool m_is_connected;
};
    
} // namespace pirates_speed
