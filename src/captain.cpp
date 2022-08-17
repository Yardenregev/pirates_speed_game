#include "../include/captain.hpp"
#include <iostream>/*std cout cin*/

namespace pirates_speed
{
    Captain::Captain(Commander &commander)
        : Callback<const std::string &>(commander),
          m_commander(commander)
    {
    }
    
    void Captain::Update(const std::string &command)
    {
        std::cout << "Captain: " << command << std::endl;
    }

    void Captain::DeathUpdate()
    {
        std::cout << "Captain: I am dead!" << std::endl;
    }
} // namespace pirates_speed
