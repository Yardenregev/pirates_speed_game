#include "../include/user.hpp"
// #include <memory>
#include <iostream>/*std cout cin*/
using namespace pirates_speed;

void TestGame(const std::string & captain_name, size_t num_of_crew_pirates,
              const std::string & ip_address, int port)
{



    User user(captain_name, num_of_crew_pirates, ip_address, port);

    user.Register();
    std::cout << "Registered" << std::endl;
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
    std::string captain_name = "Amir";
    size_t num_of_crew_pirates = 3;
    std::string ip_address = "10.10.0.151";
    int port = 8080;

    TestGame(captain_name, num_of_crew_pirates, ip_address, port);




    return 0;
}
