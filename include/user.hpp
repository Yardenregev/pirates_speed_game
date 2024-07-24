#pragma once
#include "tcp_client.hpp"
#include <string>

namespace pirates_speed
{

class User
{
public:
    enum RegistrationStatus{
        REGISTRATION_SUCCESS,
        REGISTRATION_FAILURE
    };
public:
    explicit User(const std::string & name, size_t num_of_pirates,
                  const std::string & ip_address, int port
                  );
    RegistrationStatus Register();
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
    RegistrationStatus IsConnectedToGame();
};

} // namespace pirates_speed