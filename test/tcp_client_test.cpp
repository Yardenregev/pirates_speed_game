#include "../include/tcp_client.hpp"

#include <iostream>
#include <string>

using namespace pirates_speed;

int main()
{
    TCPClient client("localhost", 8080, "10.10.0.151");
    client.SendMessage("Hello World");
    std::cout << client.ReceiveMessage() << std::endl;
    return 0;
}
