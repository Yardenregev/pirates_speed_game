#pragma once
#include "../crew_pirate.hpp"

namespace pirates_speed
{

    class Cleaner :public CrewPirate
    {
    public:
        Cleaner(const std::string &name);
        void ExecuteCommand();
    };

    class Cook : public CrewPirate
    {
    public:
        Cook(const std::string &name);
        void ExecuteCommand();
    };

    class Sailor :public CrewPirate
    {
    public:
        Sailor(const std::string &name);
        void ExecuteCommand();
    };

    class Looter :public CrewPirate
    {
    public:
        Looter(const std::string &name);
        void ExecuteCommand();
    };

    class Defender :public CrewPirate
    {
    public:
        Defender(const std::string &name);
        void ExecuteCommand();
    };

    class CleanCommand :public Command
    {
    public:
        CleanCommand();
        void Execute();
    };

    class CookCommand :public Command
    {
    public:
        CookCommand();
        void Execute();
    };

    class SailCommand :public Command
    {
    public:
        SailCommand();
        void Execute();
    };

    class LootCommand :public Command
    {
    public:
        LootCommand();
        void Execute();
    };

    class DefendCommand :public Command
    {
    public:
        DefendCommand();
        void Execute();
    };




} // namespace pirates_speed