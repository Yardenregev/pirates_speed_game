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
    std::cout << m_name << " is ";
    m_command->Execute();
}



const std::string &CrewPirate::GetName() const
{
    return m_name;
}


const std::string &CrewPirate::GetCommandName() const
{
    return m_command->GetCommandName();
}

std::string CrewPirate::ToString() const
{
    std::string str = "CrewPirate: " + GetName() + " Can " + GetCommandName();
    return str;
}

void CrewPirate::SetCommand(std::shared_ptr<Command> command)
{
    m_command = command;
}

} // namespace pirates_speed
