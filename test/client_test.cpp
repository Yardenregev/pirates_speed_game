#include "../include/tcp_client.hpp"
// #include <memory>
#include <iostream>/*std cout cin*/
using namespace pirates_speed;

void TestGame()
{
    TCPClient tcp_client(8080,"10.10.0.151");
    tcp_client.Connect();

    std::string message = tcp_client.ReceiveMessage();
    std::cout << "Captain: " << message << std::endl;
}

int main ()
{
    TestGame();




    return 0;
}
