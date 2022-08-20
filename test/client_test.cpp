#include "../include/user.hpp"
// #include <memory>
#include <iostream>/*std cout cin*/
using namespace pirates_speed;

void TestGame()
{
    // TCPClient tcp_client(8080,"10.10.0.151");
    // tcp_client.Connect();


    User user("amit",5,"192.168.68.109",8080);

    user.Register();
    std::string message = user.ReceiveMessage();
    while(user.CheckGameOver(message))
    {
        std::cout << "Captain: " << message << std::endl;
        size_t choice = 0;
        std::cin >> choice;
        user.SendMessage(std::to_string(choice));
        user.ShowReply();
        message = user.ReceiveMessage();
    }

}

int main ()
{
    TestGame();




    return 0;
}
