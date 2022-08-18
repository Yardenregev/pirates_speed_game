#include "../include/crew_pirate_factory.hpp"
#include <iostream>/*std cout cin*/

using namespace pirates_speed;

class Cook : public CrewPirate
{
public:
    Cook(const std::string &name, std::shared_ptr<Command> command)
    : CrewPirate(name, command)
    {
    }
};

class CookCommand : public Command
{
public:
    CookCommand()
    : Command("Cook")
    {
    }
    
    void Execute()
    {
        std::cout << "Cooking" << std::endl;
    }
};


static CrewPirate* CreateCook(const std::string &name,std::shared_ptr<Command> command)
{
    return new Cook(name, command);
}


void TestPirateFactory()
{
    CrewPirateFactory crew_pirate_factory;
    crew_pirate_factory.AddNewCrewPirate("Cook", CreateCook);
    CrewPirate *cooker = crew_pirate_factory.CreateCrewPirate("Cook", "Bob", std::make_shared<CookCommand>());

    cooker->ExecuteCommand();
    cooker->Print();
    delete cooker;
}


int main ()
{
    TestPirateFactory();




    return 0;
}
