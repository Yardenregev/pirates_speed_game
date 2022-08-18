#include "../include/command.hpp"

namespace pirates_speed
{
    
    
    Command::Command(const std::string &command_name)
    : m_command_name(command_name)
    {
    }

    void Command::SetCommandName(const std::string &command_name)
    {
        m_command_name = command_name;
    }

    const std::string &Command::GetCommandName() const
    {
        return m_command_name;
    }
    
    
} // namespace pirates_speed