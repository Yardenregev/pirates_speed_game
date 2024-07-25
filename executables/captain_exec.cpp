#include <iostream>/*std cout cin*/
#include <thread>

#include "../include/user.hpp"
#include "../include/default_values.hpp"

using namespace pirates_speed;

int TestGame(const std::string & captain_name, 
              const std::string & ip_address, int port,size_t num_of_crew_pirates = 5);

int TestGame(const std::string & captain_name,
              const std::string & ip_address, int port, size_t num_of_crew_pirates)
{

    User user(captain_name, num_of_crew_pirates, ip_address, port);

    if (User::REGISTRATION_FAILURE == user.Register())
    {
        return 1;
    }
    std::cout << "Registered, waiting for game to start..." << std::endl;
    user.StartGame();

    return 0;

}

int main ()
{
    std::string captain_name;
    int captain_port;
    std::string captain_ip_address;
    std::cout << "Enter captain name: ";
    std::cin >> captain_name;
    std::cout << "Enter game port ["<< DefaultValues::getDefaultPort()<<"]: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string port_str;
    std::getline(std::cin, port_str);
    try
    {
        captain_port = std::stoi(port_str);
    }
    catch (...)
    {
        captain_port = DefaultValues::getDefaultPort();
    }

    std::cout << "Enter game ip address: ";
    std::cin >> captain_ip_address;

    if(captain_name.empty() || captain_ip_address.empty() || captain_port == 0)
    {
        std::cout << "Invalid captain name, ip address or port" << std::endl;
        return 1;
    }

    return TestGame(captain_name, captain_ip_address, captain_port);
}
