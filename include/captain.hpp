#pragma once

#include <string>
#include "server.hpp"
#include "crew_pirate.hpp"
#include "inventory.hpp"
#include "tcp_client.hpp"

namespace pirates_speed
{
    class Captain
    {
        public:
            explicit Captain(const std::string & name,
                             const Inventory<std::string, std::shared_ptr<CrewPirate>> & game_inventory,
                             size_t num_of_crew_pirates = 5);
            bool IsWinner() const;
            std::string GetName() const;
            bool HandleAnswer(std::shared_ptr<Answer> answer, const std::string &command);
            std::string GetInventoryString();
            void AddRandomPirate();
        private:
            const Inventory<std::string,std::shared_ptr<CrewPirate>> &m_game_inventory;
            std::string m_name;
            Inventory<size_t,std::shared_ptr<CrewPirate>> m_personal_inventory;
    };
} // namespace pirates_speed