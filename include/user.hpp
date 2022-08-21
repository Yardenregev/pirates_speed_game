#pragma once
#include "tcp_client.hpp"
#include <string>

namespace pirates_speed
{

class User
{
public:
    explicit User(const std::string & name, size_t num_of_pirates,
                  const std::string & ip_address, int port
                  );
    void Register();
    void SendMessage(const std::string &message);
    std::string ReceiveMessage();
    void ShowReply();
    bool IsGameOver(const std::string &message);
    void StartGame();

private:
    TCPClient m_tcp_client;
    std::string m_name;
    size_t m_num_of_pirates;

private:
    void SendUserDetails();
};

} // namespace pirates_speed