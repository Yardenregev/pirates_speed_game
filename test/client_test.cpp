#include "../include/tcp_client.hpp"
// #include <memory>
#include <iostream>/*std cout cin*/
using namespace pirates_speed;

void TestGame()
{
    TCPClient tcp_client(8080,"10.10.0.151");
    tcp_client.Connect();

    std::string message = tcp_client.ReceiveMessage();
    while(message != "End of game")
    {
        std::cout << "Captain: " << message << std::endl;
        size_t choice = 0;
        std::cin >> choice;
        tcp_client.SendMessage(std::to_string(choice));
        message = tcp_client.ReceiveMessage();
    }
}

int main ()
{
    TestGame();




    return 0;
}
