#pragma once

#include <string>
#include "../include/design_patterns/dispatcher.hpp"
#include "commander.hpp"
#include "crew_pirate.hpp"
#include "inventory.hpp"

namespace pirates_speed
{
    class Captain : public Callback <const std::string &>
    {
        public:
            explicit Captain(Commander &commander, const std::string & name,
                             const Inventory<std::string, std::shared_ptr<CrewPirate>> & game_inventory
                             ,size_t num_of_crew_pirates = 5);
            void Update(const std::string &given_command);
            void DeathUpdate();
            bool IsWinner() const;
            std::string GetName() const;
        private:
            const Commander &m_commander;
            const Inventory<std::string,std::shared_ptr<CrewPirate>> &m_game_inventory;
            std::string m_name;
            Inventory<size_t,std::shared_ptr<CrewPirate>> m_personal_inventory;
            static bool m_was_command_answered;
            void PrintInventory();
            void HandleInput(const std::string &given_command);
    };
} // namespace pirates_speed