#pragma once
#include "commander.hpp"
#include "captain.hpp"
#include "inventory.hpp"

namespace pirates_speed
{
    
class Game
{
    public:
        // make game a singleton
        Game();
        ~Game();
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

    public:
        static Game& GetInstance();
        void AddPirateToGameInventory(const std::string &role, std::shared_ptr<CrewPirate> pirate);
        void AddCaptain(const std::string & name, size_t num_of_crew_pirates = 5);
        void StartGame();
        void EndGame();

    private:
        Commander m_commander;
        std::vector<std::shared_ptr<Captain>> m_captains;
        std::shared_ptr<Captain> m_winner;
        Inventory<std::string, std::shared_ptr<CrewPirate>> m_game_pirate_inventory;
        bool CheckIfGameIsOver();
        void PrintGameOver();

};
    
} // namespace pirates_speed