#include "pirate_types.hpp"

namespace pirates_speed
{
    CleanCommand::CleanCommand()
    : Command("Clean")
    {
    }

    void CleanCommand::Execute()
    {
        std::cout << "Cleaning the ship..." << std::endl;
    }

    CookCommand::CookCommand()
    : Command("Cook")
    {
    }

    void CookCommand::Execute()
    {
        std::cout << "cooking..." << std::endl;
    }

    SailCommand::SailCommand()
    : Command("Sail")
    {
    }

    void SailCommand::Execute()
    {
        std::cout << "sailing..." << std::endl;
    }

    LootCommand::LootCommand()
    : Command("Loot")
    {
    }

    void LootCommand::Execute()
    {
        std::cout << "looting..." << std::endl;
    }

    DefendCommand::DefendCommand()
    : Command("Defend")
    {
    }

    void DefendCommand::Execute()
    {
        std::cout << "defending..." << std::endl;
    }


    Cleaner::Cleaner(const std::string &name) 
    : CrewPirate(name, std::make_shared<CleanCommand>())
    {
    }


    Cook::Cook(const std::string &name)
    : CrewPirate(name, std::make_shared<CookCommand>())
    {
    }

    Sailor::Sailor(const std::string &name)
    : CrewPirate(name, std::make_shared<SailCommand>())
    {
    }

    Looter::Looter(const std::string &name)
    : CrewPirate(name, std::make_shared<LootCommand>())
    {
    }

    Defender::Defender(const std::string &name)
    : CrewPirate(name, std::make_shared<DefendCommand>())
    {
    }
} // namespace pirates_speed
