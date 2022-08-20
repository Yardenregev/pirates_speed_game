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

} // namespace pirates_speed