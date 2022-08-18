#include "../include/captain.hpp"
#include <iostream>/*std cout cin*/

namespace pirates_speed
{
    bool Captain::m_was_command_answered = false;

    Captain::Captain(Commander &commander,
                    const std::string & name,
                    const Inventory<std::string,std::shared_ptr<CrewPirate>> &game_inventory
                    ,size_t num_of_crew_pirates)
        : Callback<const std::string &>(commander),
          m_commander(commander),
          m_game_inventory(game_inventory),
          m_name(name),
          m_personal_inventory()
    {
        for (size_t i = 0; i < num_of_crew_pirates; ++i)
        {
            m_personal_inventory.Add(i,m_game_inventory.GetRandom());
        }

        PrintInventory();
    }
    
    void Captain::Update(const std::string &given_command)
    {
        std::cout << "Captain: " << given_command << std::endl;
        HandleInput(given_command);
    }

    void Captain::DeathUpdate()
    {
        std::cout << "Captain: I am dead!" << std::endl;
    }

    bool Captain::IsWinner() const
    {
        return m_personal_inventory.IsEmpty();
    }

    std::string Captain::GetName() const
    {
        return m_name;
    }


    void Captain::PrintInventory()
    {
        std::cout << "My Pirates: " << std::endl;
        for (auto &pirate : m_personal_inventory)
        {
            std::cout << pirate.first << ":\t";
        }

        std::cout << std::endl;

        for (auto &pirate : m_personal_inventory)
        {
            pirate.second->Print();
            std::cout << "\t";
        }

        std::cout << std::endl;
    }

    void Captain::HandleInput(const std::string & given_command)
    {
        size_t pirate_index;
        std::cin >> pirate_index;

        std::shared_ptr<CrewPirate> pirate;
        if (m_personal_inventory.Contains(pirate_index))
        {
            pirate = m_personal_inventory.Get(pirate_index);
            if (pirate->GetCommandName() == given_command)
            {
                pirate->ExecuteCommand();
                m_personal_inventory.Remove(pirate_index);
                std::cout << "Well done captain " << m_name << "!" << std::endl;
                PrintInventory();
                return;
            }    
        }

        std::cout << "Captain " << m_name << ", You have failed!" << std::endl;
        m_personal_inventory.Add(m_personal_inventory.GetSize(),m_game_inventory.GetRandom());
        PrintInventory();
    }
} // namespace pirates_speed
