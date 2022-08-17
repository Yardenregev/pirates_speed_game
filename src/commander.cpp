#include "../include/commander.hpp"
#include "../include/design_patterns/singleton.hpp"

namespace pirates_speed
{

    Commander& Commander::GetInstance()
    {
        return Singleton<Commander>::GetInstance();
    }
    
    void Commander::ShoutCommand(const std::string &command)
    {
        NotifyAll(command);
    }
    
} // namespace pirates_speed
