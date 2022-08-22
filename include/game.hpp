#pragma once
#include <thread>
#include <condition_variable>
#include <mutex>
#include "server.hpp"
#include "captain.hpp"
#include "inventory.hpp"
namespace pirates_speed
{
    
class Game
{
    public:
        Game(const std::string & commander_name, int port, const std::string & ip_address);
        ~Game() = default;
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

    public:
        void AddPirateToGameInventory(const std::string &role, std::shared_ptr<CrewPirate> pirate);
        void AddCaptain();
        void StartGame();
        void EndGame();
        void ReceiveFromAll();
    private:
        Server m_server;
        std::string m_commander_name;
        std::map<std::string, std::shared_ptr<Captain>> m_captains;
        std::shared_ptr<Captain> m_winner;
        Inventory<std::string, std::shared_ptr<CrewPirate>> m_game_pirate_inventory;
    
        bool CheckIfGameIsOver();
        void SendGameOver();
        void RegisterCaptain();
        void AddPirateForAllButCorrectCaptain(const std::string & correct_captain_name);
        

        void ConnectCommanderToCaptain();
        void ConnectCaptainToCommander(std::shared_ptr<Captain> &captain);
        void ConnectCommanderAndCaptain(std::shared_ptr<Captain> &captain);
        void HandleAnswers(const std::string &command);
        void SendInventoriesToAllCaptains();
        std::string GetCaptainInventory(const std::string &captain_name);
        bool MakeCaptainHandleAnswer(const std::string &captain_name,std::shared_ptr<Answer> answer, const std::string &command);
};
    
} // namespace pirates_speed