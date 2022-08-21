#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace pirates_speed
{


    template <typename T>
    class WaitableQueue
    {
        public:
            WaitableQueue();
            ~WaitableQueue() = default;
            WaitableQueue(const WaitableQueue&) = delete;
            WaitableQueue& operator=(const WaitableQueue&) = delete;
        public:
            void Push(const T &data);
            void Pop(T &data);
            bool Empty() const;
            size_t Size() const;
        private:
            std::priority_queue<T> m_queue;
            std::mutex m_mutex;
            std::condition_variable m_condition_variable;
    };


    template <typename T>
    WaitableQueue<T>::WaitableQueue()
    : m_queue(),
      m_mutex(),
      m_condition_variable()
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
        data = m_queue.top();
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