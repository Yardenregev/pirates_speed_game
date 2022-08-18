#include "../include/waitable_queue.hpp"

namespace pirates_speed
{
    template <typename T>
    void WaitableQueue<T>::Push(const T &data)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        
        m_queue.push(data);
    }
    template <typename T>
    void WaitableQueue<T>::Pop(T &data)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
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
