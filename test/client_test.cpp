#include "../include/user.hpp"
// #include <memory>
#include <iostream>/*std cout cin*/
using namespace pirates_speed;

void TestGame(const std::string & captain_name, size_t num_of_crew_pirates,
              const std::string & ip_address, int port)
{
    // TCPClient tcp_client(8080,"10.10.0.151");
    // tcp_client.Connect();


    User user(captain_name, num_of_crew_pirates, ip_address, port);

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

int main (int argc, char *argv[])
{
    std::string name = argv[1];
    size_t num_of_pirates = std::stoi(argv[2]);
    std::string ip_address = argv[3];
    int port = std::stoi(argv[4]);

    TestGame(name, num_of_pirates, ip_address, port);




    return 0;
}
