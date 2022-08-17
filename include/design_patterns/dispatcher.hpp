#pragma once

#include <vector>   // vector

namespace pirates_speed
{

template <typename T>
class Callback;

template <typename T>
class Dispatcher
{
public:
    Dispatcher() : m_observers() {}
    virtual void Subscribe(Callback<T>* callback_);
    virtual void Unsubscribe(Callback<T>* callback_);
    virtual void NotifyAll(T event_);

    virtual ~Dispatcher();

private:
    std::vector<Callback<T>*> m_observers;
};

template <typename T>
class Callback
{
public:
     Callback(Dispatcher<T> &dispatcher_) : m_dispatcher(dispatcher_) {
            m_dispatcher.Subscribe(this);
     }
    virtual void Update(T event_) = 0;
    virtual void DeathUpdate() = 0;
    virtual ~Callback() = 0;
private:
    Dispatcher<T> &m_dispatcher;
};

template <typename T>
void Dispatcher<T>::Subscribe(Callback<T>* callback_)
{
    m_observers.push_back(callback_);
}

template <typename T>
void Dispatcher<T>::Unsubscribe(Callback<T>* callback_)
{
    for(size_t i = 0; i < m_observers.size();i++)
    {
        if(m_observers[i] == callback_)
        {
            m_observers.erase(m_observers.begin() + i);
            break;
        }
    }
}

template <typename T>
void Dispatcher<T>::NotifyAll(T event_)
{
    for(size_t i = 0; i < m_observers.size();i++)
    {
        m_observers[i]->Update(event_);
    }
}

template <typename T>
Dispatcher<T>::~Dispatcher()
{
    for(size_t i = 0; i < m_observers.size();i++)
    {
        m_observers[i]->DeathUpdate();
    }
}

template <typename T>
Callback<T>::~Callback()
{
    m_dispatcher.Unsubscribe(this);
}

} // namespace pirates_speed