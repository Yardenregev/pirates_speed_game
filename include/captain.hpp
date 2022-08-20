#pragma once

#include <string>
#include "../include/design_patterns/dispatcher.hpp"
#include "server.hpp"
#include "crew_pirate.hpp"
#include "inventory.hpp"
#include "tcp_client.hpp"

namespace pirates_speed
{
    // class Captain : public Callback <const std::string &>
    class Captain
    {
        public:
            explicit Captain(const std::string & name,
                             const Inventory<std::string, std::shared_ptr<CrewPirate>> & game_inventory,
                            //  const std::string & ip_address, int port,
                             size_t num_of_crew_pirates = 5);
            // void Update(const std::string &given_command);
            // void DeathUpdate();
            bool IsWinner() const;
            std::string GetName() const;
            // void RecieveMessage();
            // void ConnectCommander();
            bool HandleAnswer(std::shared_ptr<Answer> answer, const std::string &command);
            std::string GetInventoryString();
        private:
            const Inventory<std::string,std::shared_ptr<CrewPirate>> &m_game_inventory;
            std::string m_name;
            Inventory<size_t,std::shared_ptr<CrewPirate>> m_personal_inventory;

            // TCPClient m_tcp_client;
            void PrintInventory();
            void HandleInput(const std::string &given_command);
            void AddRandomPirate();
    };
} // namespace pirates_speed