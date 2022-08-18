#pragma once
#include <thread>
#include <condition_variable>
#include <mutex>
#include "commander.hpp"
#include "captain.hpp"
#include "inventory.hpp"
namespace pirates_speed
{
    
class Game
{
    public:
        Game(const std::string & commander_name, int port, const std::string & ip_address);
        ~Game();
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

    public:
        void AddPirateToGameInventory(const std::string &role, std::shared_ptr<CrewPirate> pirate);
        void AddCaptain();
        void StartGame();
        void EndGame();

    private:
        std::unique_ptr<Commander> m_commander;
        std::vector<std::shared_ptr<Captain>> m_captains;
        std::shared_ptr<Captain> m_winner;
        Inventory<std::string, std::shared_ptr<CrewPirate>> m_game_pirate_inventory;
        std::mutex m_mutex;
        std::condition_variable m_condition_variable;
        
        bool CheckIfGameIsOver();
        void PrintGameOver();
        void RegisterCaptain();

        void ConnectCommanderToCaptain();
        void ConnectCaptainToCommander(std::shared_ptr<Captain> &captain);
        void ConnectCommanderAndCaptain(std::shared_ptr<Captain> &captain);

};
    
} // namespace pirates_speed