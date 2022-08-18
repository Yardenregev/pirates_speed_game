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

void CrewPirate::Print() const
{
    std::cout << "Pirate: " << m_name << " Can " << m_command->GetCommandName();
}

const std::string &CrewPirate::GetCommandName() const
{
    return m_command->GetCommandName();
}

void CrewPirate::SetCommand(std::shared_ptr<Command> command)
{
    m_command = command;
}

} // namespace pirates_speed
