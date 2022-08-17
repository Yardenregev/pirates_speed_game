#include "../include/commander.hpp"

namespace pirates_speed
{
    
    void Commander::ShoutCommand(const std::string &command)
    {
        NotifyAll(command);
    }
    
} // namespace pirates_speed
