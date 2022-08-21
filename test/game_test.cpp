#include "../include/game.hpp"

using namespace pirates_speed;

void TestGame()
{
    // std::string commander_name;
    // int commander_port;
    // std::string commander_ip_address;

    // std::cout << "Enter commander name: ";
    // std::cin >> commander_name;
    // std::cout << "Enter commander port: ";
    // std::cin >> commander_port;
    // std::cout << "Enter commander ip address: ";
    // std::cin >> commander_ip_address;

    // if(commander_name.empty() || commander_ip_address.empty() || commander_port == 0)
    // {
    //     std::cout << "Invalid commander name, ip address or port" << std::endl;
    //     return;
    // }

    Game game("yarden", 8080, "10.10.0.151");
    game.AddCaptain();

    game.StartGame();
}
int main ()
{
    TestGame();




    return 0;
}
