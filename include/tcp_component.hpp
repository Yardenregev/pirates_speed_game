#pragma once
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>


namespace pirates_speed
{
class TCPComponent
{
public:
    TCPComponent(int port, const std::string & ip_address);
    TCPComponent(const TCPComponent &) = delete;
    TCPComponent &operator=(const TCPComponent &) = delete;
    virtual ~TCPComponent() = 0;

    int GetSocket() const;

    void SendMessage(const std::string &message);

protected:
    int m_port;
    std::string m_ip_address;
    struct sockaddr_in m_server_address;
    int m_socket;
};
    
} // namespace pirates_speed
