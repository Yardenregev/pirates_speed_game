#pragma once

#include <string>

namespace pirates_speed
{
    

class Command 
{
public:
    explicit Command(const std::string &name = "Lazy");
    virtual ~Command() = default;
    virtual void Execute() = 0;

    void SetCommandName(const std::string &name);
    const std::string &GetCommandName() const;
private:
    std::string m_command_name;
};

} // namespace pirates_speed