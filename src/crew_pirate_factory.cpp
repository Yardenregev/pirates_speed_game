#include "../include/crew_pirate_factory.hpp"

namespace pirates_speed
{
    CrewPirateFactory::CrewPirateFactory()
    : m_factory()
    {
    }
    
    void CrewPirateFactory::AddNewCrewPirate(const std::string &role, std::function<CrewPirate *(const std::string &, std::shared_ptr<Command>)> crew_pirate_creator)
    {
        m_factory.Add(role, crew_pirate_creator);
    }

    CrewPirate *CrewPirateFactory::CreateCrewPirate(const std::string &role, const std::string &name,std::shared_ptr<Command> command)
    {
        return m_factory.Create(role, name, command);
    }
} // namespace pirates_speed

