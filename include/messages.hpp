#pragma once
#include <string>

class Messages{
    public:
        Messages() = delete;
        static const std::string start_round;
        static const std::string end_round;
        static const std::string connected;
        static const std::string name_taken;
        static const std::string correct_answer;
        static const std::string wrong_answer;
        static const std::string too_slow_answer;
        
};

