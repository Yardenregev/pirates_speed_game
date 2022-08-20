#include "../include/waitable_queue.hpp"

namespace pirates_speed
{

    template <typename T>
    WaitableQueue<T>::WaitableQueue()
    : m_queue()
    {
    }


    template <typename T>
    void WaitableQueue<T>::Push(const T &data)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(data);
        m_condition_variable.notify_one();
    }

    template <typename T>
    void WaitableQueue<T>::Pop(T &data)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while(m_queue.empty())
        {
            m_condition_variable.wait(lock);
        }
        data = m_queue.front();
        m_queue.pop();
    }
    template <typename T>
    bool WaitableQueue<T>::Empty() const
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }
    template <typename T>
    size_t WaitableQueue<T>::Size() const
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.size();
    }
} // namespace pirates_speed
