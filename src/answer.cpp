#include "../include/answer.hpp"

namespace pirates_speed
{
    Answer::Answer(const std::string &captain_name, const std::string & answer, Priority priority)
          :m_captain_name(captain_name),
           m_answer(answer),
           m_priority(priority)
    {
    }

    const std::string & Answer::GetCaptainName() const
    {
        return m_captain_name;
    }
    
    const std::string & Answer::GetAnswer() const
    {
        return m_answer;
    }

    bool Answer::operator<(const Answer& other) const
    {
        return m_priority < other.m_priority;
    }

    Priority Answer::GetPriority() const
    {
        return m_priority;
    }
    
} // namespace pirates_speed
