#include "../include/user.hpp"
#include <iostream>/*std cout cin*/
using namespace pirates_speed;

void TestGame(const std::string & captain_name, 
              const std::string & ip_address, int port,size_t num_of_crew_pirates = 5);

void TestGame(const std::string & captain_name,
              const std::string & ip_address, int port, size_t num_of_crew_pirates)
{

    User user(captain_name, num_of_crew_pirates, ip_address, port);

    user.Register();
    std::cout << "Registered" << std::endl;
    user.StartGame();

}

int main ()
{
    std::string captain_name;
    int captain_port;
    std::string captain_ip_address;
    std::cout << "Enter captain name: ";
    std::cin >> captain_name;
    std::cout << "Enter game port: ";
    std::cin >> captain_port;
    std::cout << "Enter game ip address: ";
    std::cin >> captain_ip_address;

    if(captain_name.empty() || captain_ip_address.empty() || captain_port == 0)
    {
        std::cout << "Invalid captain name, ip address or port" << std::endl;
        return 1;
    }

    TestGame(captain_name, captain_ip_address, captain_port);




    return 0;
}
