#pragma once

namespace pirates_speed
{
    
class Game
{
    public:
        // make game a singleton
        Game() = delete;
        ~Game() = delete;
        Game(const Game&) = delete;
        Game& operator=(const Game&) = delete;

    public:
        static Game& GetInstance();
        void StartGame();
        void EndGame();
};
    
} // namespace pirates_speed