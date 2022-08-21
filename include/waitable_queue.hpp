#pragma once

#include <cstddef>              // size_t
#include <mutex>                // mutex
#include <condition_variable>   // condition_variable
#include <chrono>               // duration
#include <queue>                // queue

namespace pirates_speed
{

template <typename T, typename Q=std::queue<T>>
class WaitableQueue
{

public:
    explicit WaitableQueue();
    WaitableQueue(const WaitableQueue&) = delete;
    WaitableQueue& operator=(const WaitableQueue&) = delete;
    ~WaitableQueue() noexcept;

    void Push(const T& element);
    
    void Pop(T& _element);
    template <typename R = int64_t, typename P = std::milli>
    bool Pop(T&, const std::chrono::duration<R, P>&);
    bool IsEmpty() const;
    void Clear();
private:
    Q m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cond;

private:
    void PopTopElement(T& _element);
};

/************ waitable q implementation *********************/
template <typename T, typename Q>
WaitableQueue<T,Q>::WaitableQueue()
    :m_queue(),m_mutex(), m_cond()
{
    //empty
}


template <typename T, typename Q>
WaitableQueue<T,Q>::~WaitableQueue() noexcept
{
    //empty
}

template <typename T, typename Q>
void WaitableQueue<T,Q>:: Push(const T& element)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_queue.push(element);
    lock.unlock();
    m_cond.notify_one();
}

template <typename T, typename Q>
void WaitableQueue<T,Q>:: Pop(T& _element)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while(m_queue.empty())
    {
        m_cond.wait(lock);
    }

    PopTopElement(_element);
}

template <typename T, typename Q>
template <typename R, typename P>
bool WaitableQueue<T, Q>::Pop(T& _element,  const std::chrono::duration<R, P>& dur_)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while(m_queue.empty())
    {
        if (false == m_cond.wait_for(lock,dur_,[]{return false;}))
        {
            return false;
        }
    }

    PopTopElement(_element);

    return true;
}

template <typename T, typename Q>
bool WaitableQueue<T,Q>::IsEmpty() const
{
    return m_queue.empty();
}

template <typename T, typename Q>
void WaitableQueue<T,Q>::PopTopElement(T& _element)
{
    _element = m_queue.front();
    m_queue.pop();
}


} // namespace ilrd










