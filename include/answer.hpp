#include <string>

namespace pirates_speed
{
    enum class Priority
    {
        ANSWER,
        END_ROUND
    };

    class Answer
    {
        public:
            Answer(const std::string &captain_name = "", const std::string & answer = "", Priority priority = Priority::ANSWER);
            ~Answer() = default;
            Answer(const Answer&) = default;
            Answer& operator=(const Answer&) = default;

        public:
            const std::string & GetAnswer() const;
            const std::string & GetCaptainName() const;
            Priority GetPriority() const;
            bool operator<(const Answer& other) const;

        private:
            std::string m_captain_name;
            std::string m_answer;
            Priority m_priority;

    };
} // namespace pirates_speed
