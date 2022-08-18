#pragma once

#include <map>
#include <memory>
#include <functional>

namespace pirates_speed
{
    
template <typename KEY, typename BASE, typename... Args>
class Factory
{
public:
    Factory();
    void Add(KEY key, std::function<BASE(Args... args)> factory);
    BASE Create(KEY key, Args... args);
    void Remove(KEY key);
    void RemoveAll();
private:
    std::map<KEY, std::function<BASE(Args... args)>> m_factory;
};

template <typename KEY, typename BASE, typename... Args>
Factory<KEY, BASE, Args...>::Factory()
: m_factory()
{
}

template <typename KEY, typename BASE, typename... Args>
void Factory<KEY, BASE, Args...>::Add(KEY key, std::function<BASE(Args... args)> factory)
{
    m_factory[key] = factory;
}

template <typename KEY, typename BASE, typename... Args>
BASE Factory<KEY, BASE, Args...>::Create(KEY key, Args... args)
{
    if(m_factory.find(key) == m_factory.end())
    {
        throw std::runtime_error("No such key in factory");
    }

    return m_factory[key](args...);
}

template <typename KEY, typename BASE, typename... Args>
void Factory<KEY, BASE, Args...>::Remove(KEY key)
{
    if(m_factory.find(key) == m_factory.end())
    {
        throw std::runtime_error("No such key in factory");
    }

    m_factory.erase(key);
}

template <typename KEY, typename BASE, typename... Args>
void Factory<KEY, BASE, Args...>::RemoveAll()
{
    m_factory.clear();
}

} // namespace pirates_speed
