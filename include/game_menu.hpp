#pragma once
#include "game.hpp"
namespace pirates_speed
{
class GameMenu
{
public:
    GameMenu();
    void ShowMenu();
    void TakeChoice();
    void SetUpGame();
    void AddCaptain();
    void StartGame();

private:
    std::shared_ptr<Game> m_game;
    bool m_set_up_game;
    size_t m_captain_count;
};

} // namespace pirates_speed