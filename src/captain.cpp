#include "../include/captain.hpp"
#include <iostream>/*std cout cin*/

namespace pirates_speed
{

    Captain::Captain(const std::string & name,
                             const Inventory<std::string, std::shared_ptr<CrewPirate>> & game_inventory,
                            //  const std::string & ip_address, int port,
                             size_t num_of_crew_pirates)
          :m_game_inventory(game_inventory),
           m_name(name),
           m_personal_inventory()
    {
        for (size_t i = 0; i < num_of_crew_pirates; ++i)
        {
            m_personal_inventory.Add(i,m_game_inventory.GetRandom());
        }

    }
    

    bool Captain::IsWinner() const
    {
        return m_personal_inventory.IsEmpty();
    }

    std::string Captain::GetName() const
    {
        return m_name;
    }


    bool Captain::HandleAnswer(std::shared_ptr<Answer> answer, const std::string &command)
    {
        size_t ind_answer = std::stoi(answer->GetAnswer());

        if(m_personal_inventory.Contains(ind_answer))
        {
            std::shared_ptr<CrewPirate> pirate = m_personal_inventory.Get(ind_answer);
            if(pirate->GetCommandName() == command)
            {
                pirate->ExecuteCommand();
                m_personal_inventory.Remove(ind_answer);
                return true;
            }
        }

        // AddRandomPirate();

        return false;
    }

    void Captain::AddRandomPirate()
    {
        size_t ind = m_personal_inventory.GetSize();
        m_personal_inventory.Add(ind,m_game_inventory.GetRandom());
    }

    std::string Captain::GetInventoryString()
    {
        std::string inventory;
        for (auto &pirate : m_personal_inventory)
        {
            inventory += std::to_string(pirate.first) + "\t";
        }

        inventory += "\n";

        for (auto &pirate : m_personal_inventory)
        {
            inventory += pirate.second->ToString() + "\t";
        }

        return inventory;

    }
    
} // namespace pirates_speed
