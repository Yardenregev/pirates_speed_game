#pragma once

#include <vector>
#include <memory>
namespace pirates_speed
{
    
template<typename T>
class Callback;

template<typename T>
class Dispatcher
{

    public:
        Dispatcher() = default;
        ~Dispatcher();
        Dispatcher(const Dispatcher &) = delete;
        Dispatcher& operator= (const Dispatcher &) = delete;

    public:
        void Subscribe(std::shared_ptr<Callback<T>>);
        void Unsubscribe(std::shared_ptr<Callback<T>>);
        void NotifyAll(T event);

    private:
        std::vector<std::shared_ptr<Callback<T>>> m_vec;

};

template<typename T>
class Callback
{
    public:
        Callback(Dispatcher<T> & disp);
        ~Callback();
        Callback(const Callback &) = delete;
        Callback& operator= (const Callback &) = delete;

    public:
        void Update(T event) = 0;
        void Unsubscribe();
        void Subscribe(Dispatcher<T> & disp);

    private:
        Dispatcher<T>& m_disp;
        bool m_subscribed;
};

template<typename T>
Dispatcher<T>::~Dispatcher()
{
    for (auto & cb : m_vec)
    {
        cb->Unsubscribe();
    }
}

template<typename T>
void Dispatcher<T>::Subscribe(std::shared_ptr<Callback<T>> cb)
{
    m_vec.push_back(cb);
    cb->Subscribe(*this);
}

template<typename T>
void Dispatcher<T>::Unsubscribe(std::shared_ptr<Callback<T>> cb)
{
    for (size_t i = 0; i < m_vec.size(); i++)
    {
        if (m_vec[i] == cb)
        {
            m_vec.erase(m_vec.begin() + i);
            break;
        }
    }
}

template<typename T>
void Dispatcher<T>::NotifyAll(T event)
{
    for (size_t i = 0; i < m_vec.size(); i++)
    {
        m_vec[i]->Update(event);
    }
}


template<typename T>
Callback<T>::Callback(Dispatcher<T> & disp) : m_disp(disp), m_subscribed(false)
{
    m_disp.Subscribe(this);
    m_subscribed = true;
}

template<typename T>
Callback<T>::~Callback()
{
    if (m_subscribed)
    {
        m_disp.Unsubscribe(this);
        m_subscribed = false;
    }
}


} // namespace pirates_speed