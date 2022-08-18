#pragma once


#include "crew_pirate.hpp"
#include "./design_patterns/factory.hpp"

namespace pirates_speed
{
    

class CrewPirateFactory
{
public:
    CrewPirateFactory();
    CrewPirate *CreateCrewPirate(const std::string &role, const std::string &name,std::shared_ptr<Command> command);
    void AddNewCrewPirate(const std::string &role, std::function<CrewPirate *(const std::string &,std::shared_ptr<Command>)> crew_pirate_creator);

private:
    Factory<std::string, CrewPirate *,const std::string &, std::shared_ptr<Command>> m_factory;
};

} // namespace pirates_speed