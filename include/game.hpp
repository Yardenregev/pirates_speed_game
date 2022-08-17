#pragma once
#include "singleton.hpp"

class Game : public Singleton
{
    public:
        void StartGame();
        void EndGame();
};
    