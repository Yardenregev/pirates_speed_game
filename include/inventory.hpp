#pragma once
#include <map>
#include <iostream>/*std cout cin*/

namespace pirates_speed
{
template <typename KEY, typename TYPE>
class Inventory
{
public:
    Inventory();
    void Add(KEY key, TYPE type);
    TYPE Get(KEY key) const;
    void Remove(KEY key);
    void RemoveAll();
    TYPE GetRandom() const;

    bool IsEmpty() const;
    bool Contains(KEY key) const;
    size_t GetSize() const;


    typename std::map<KEY, TYPE>::iterator begin();
    typename std::map<KEY, TYPE>::iterator end();

private:
    std::map<KEY, TYPE> m_inventory;
};


template <typename KEY, typename TYPE>
Inventory<KEY, TYPE>::Inventory()
: m_inventory()
{
}


template <typename KEY, typename TYPE>
void Inventory<KEY, TYPE>::Add(KEY key, TYPE type)
{
    m_inventory[key] = type;
}



template <typename KEY, typename TYPE>
TYPE Inventory<KEY, TYPE>::Get(KEY key) const
{
    auto answer = m_inventory.at(key);
    if(answer == nullptr)
    {
        throw std::runtime_error("No such pirate");
    }

    return answer;
}


template <typename KEY, typename TYPE>
void Inventory<KEY, TYPE>::Remove(KEY key)
{
    if(m_inventory.find(key) == m_inventory.end())
    {
        throw std::runtime_error("No such key in inventory");
    }

    m_inventory.erase(key);
}


template <typename KEY, typename TYPE>
void Inventory<KEY, TYPE>::RemoveAll()
{
    m_inventory.clear();
}


template <typename KEY, typename TYPE>
TYPE Inventory<KEY, TYPE>::GetRandom() const
{
    if(IsEmpty())
    {
        throw std::runtime_error("Inventory is empty");
    }
    
    auto it = m_inventory.begin();
    std::advance(it, rand() % m_inventory.size());
    return it->second;
}



template <typename KEY, typename TYPE>
typename std::map<KEY, TYPE>::iterator Inventory<KEY, TYPE>::begin()
{
    return m_inventory.begin();
}


template <typename KEY, typename TYPE>
typename std::map<KEY, TYPE>::iterator Inventory<KEY, TYPE>::end()
{
    return m_inventory.end();
}

template <typename KEY, typename TYPE>
bool Inventory<KEY, TYPE>::IsEmpty() const
{
    return m_inventory.empty();
}


template <typename KEY, typename TYPE>
bool Inventory<KEY, TYPE>::Contains(KEY key) const
{
    return (m_inventory.at(key) != nullptr);
}


template <typename KEY, typename TYPE>
size_t Inventory<KEY, TYPE>::GetSize() const
{
    return m_inventory.size();
}






} // namespace pirates_speed
