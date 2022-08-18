#include "../include/commander.hpp"
#include "../include/design_patterns/singleton.hpp"
#include <iostream>/*std cout cin*/

namespace pirates_speed
{

    
    void Commander::ShoutCommand(const std::string &command)
    {
        m_tcp_dispatcher.SendMessageToAll(command);
    }

    Commander::Commander(const std::string & name, int port, const std::string & ip_address)
        : m_tcp_dispatcher(port, ip_address),
          m_name(name),
          answers(),
          m_answered(false)
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
    

    void Commander::ReciveAnswers()
    {
        while(m_answered == false)
        {
            std::string answer = m_tcp_dispatcher.ReceiveMessage();
            answers.Push(answer);
        }
    }

    void Commander::HandleAnswers()
    {
        while(m_answered == false)
        {    
            std::thread t(&Commander::ReciveAnswers, this);
            std::string answer;
            answers.Pop(answer);
        }
    }
} // namespace pirates_speed
