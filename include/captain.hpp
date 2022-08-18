#pragma once

#include <string>
#include "../include/design_patterns/dispatcher.hpp"
#include "commander.hpp"

namespace pirates_speed
{
    class Captain : public Callback <const std::string &>
    {
        public:
            explicit Captain(Commander &commander);
            void Update(const std::string &command);
            void DeathUpdate();
        private:
            Commander &m_commander;
    };
} // namespace pirates_speed