#include "../include/commander.hpp"
#include "../include/design_patterns/singleton.hpp"
#include <iostream>/*std cout cin*/

namespace pirates_speed
{

    // Commander& Commander::GetInstance(const std::string & name, int port, const std::string & ip_address)
    // {
    //     return Singleton<Commander,const std::string &, int,
    //                  const std::string &>::GetInstance(name, port, ip_address);
    // }
    
    void Commander::ShoutCommand(const std::string &command)
    {
        m_tcp_dispatcher.SendMessageToAll(command);
    }

    Commander::Commander(const std::string & name, int port, const std::string & ip_address)
        : m_tcp_dispatcher(port, ip_address)
        , m_name(name)
    {
    }

    void Commander::AddCaptain()
    {
        m_tcp_dispatcher.AddClient();
    }

    std::string Commander::GetName() const
    {
        return m_name;
    }
    

    void Commander::SendMessageToLastCaptain(const std::string &command)
    {
        m_tcp_dispatcher.SendMessageToLastClient(command);
    }

    char *Commander::ReciveMessageFromLastCaptain()
    {
        return m_tcp_dispatcher.ReciveMessageFromLastClient();
    }

} // namespace pirates_speed
