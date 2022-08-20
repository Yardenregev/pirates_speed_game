#include "../include/commander.hpp"
#include "../include/captain.hpp"
using namespace pirates_speed;

void TestCommanderCaptain()
{
    Server commander = Server::GetInstance();
    Captain captain(commander);
    Captain captain2(commander);
    Captain captain3(commander);
    commander.ShoutCommand("Cook dinner");
}

int main ()
{
    TestCommanderCaptain();




    return 0;
}

