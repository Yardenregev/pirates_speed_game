#pragma once
#include "tcp_component.hpp"

namespace pirates_speed
{
class TCPClient : public TCPComponent
{
public:
    TCPClient(int port, const std::string & ip_address);
    void Connect();
};
    
} // namespace pirates_speed
