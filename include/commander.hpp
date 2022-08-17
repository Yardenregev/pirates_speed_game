#pragma once
#include "../include/design_patterns/dispatcher.hpp"
#include <string>


namespace pirates_speed
{

    class Commander : public Dispatcher<const std::string &>
    {
        public :
            static Commander & GetInstance();
        public:
            void ShoutCommand(const std::string &command);
    };
    
} // namespace pirates_speed
