#include "../include/crew_pirate.hpp"

namespace pirates_speed
{

CrewPirate::CrewPirate(const std::string &name, std::shared_ptr<Command> command)
: m_name(name), m_command(command)
{
}

CrewPirate::~CrewPirate()
{
}

void CrewPirate::ExecuteCommand()
{
    m_command->Execute();
}


} // namespace pirates_speed
