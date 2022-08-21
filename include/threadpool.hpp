#pragma once

#include <cstddef>  // size_t
#include <vector>   
#include <queue>    
#include <thread>
#include <functional>
#include <mutex>
#include <unistd.h>
#include <cstring>
#include <cassert>
#include "waitable_queue.hpp"
#include "pq_wrapper.hpp"


namespace pirates_speed
{
class ThreadPool;
void ThreadTask(ThreadPool &tp,size_t index);

// how many threads in the pool    
enum TaskPriority {
        FINISH,
        LOW,
        MEDIUM,
        HIGH,
        PAUSE
    };

template<typename Y>
class Future;

/*<-------------------------------------------------------------------------->*/

class ThreadPool
{
    class GeneralTask;
public:
    explicit ThreadPool(size_t thread_num_ = std::thread::hardware_concurrency());
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ~ThreadPool() noexcept;

    template <typename Y>
    Future<Y> AddTask(const std::function<Y()>& task, TaskPriority priority);
    void AddTask(const std::function<void()>& task, TaskPriority priority);
    
    
    void ResizePool(size_t);
    void Resume();
    void Pause(); // Stop Thread Assignment



private:
    void PoisonApple(TaskPriority priority = TaskPriority::FINISH);
    class Thread;
    size_t m_num_of_threads;
    std::vector<Thread*> m_vec;
    WaitableQueue<std::shared_ptr<GeneralTask>, PQ<std::shared_ptr<GeneralTask>>> m_wqueue;
    bool m_is_done;
    bool m_is_paused;
    std::mutex m_mutex_can_pop;
    std::vector<bool> m_vec_should_terminate;

private:

private:
    class GeneralTask
    {
        public:
            virtual void operator() ()= 0;
            virtual ~GeneralTask() noexcept = default;
    };
    template <typename Y>
    class TemplatedTask;
    template <typename Y>
    class Task : public ThreadPool::GeneralTask
    {


    public:

        Task(const std::function<Y()>& task, TaskPriority priority)
            :m_task(task), m_priority(priority), m_is_valid(false)
            ,m_mutex(), m_cond_has_res()
        {
            //empty
        }
        Task(const Task& other)
            :m_task(other.m_task), m_priority(other.m_priority),
             m_is_valid(false),m_mutex(), m_cond_has_res()
        {
            //empty
        }

        Task& operator=(const Task& other)
        {
            if (this != &other)
            {
                m_task = other.m_task;
                m_priority = other.m_priority;
            }
            return *this;
        }
        
        virtual ~Task() noexcept
        {
            //empty
        }

        bool operator<(const Task& other) const
        {
            return m_priority < other.m_priority;
        }

        virtual void operator()()
        {
            m_task();
            m_is_valid = true;
            m_cond_has_res.notify_one();
        }

    private:
        friend class Future<Y>;
        friend class TemplatedTask<Y>;
        template <typename Z>
        friend Z& GetRes(ThreadPool::TemplatedTask<Z>& task);
        std::function<Y()> m_task;
        TaskPriority m_priority;
        bool m_is_valid;
        std::mutex m_mutex;
        std::condition_variable m_cond_has_res;
    };

    template <typename Y>
    class TemplatedTask : public Task<Y>
    {
        template <typename Z>
        friend Z& GetRes(ThreadPool::TemplatedTask<Z>& task);
    public:

        TemplatedTask(const std::function<Y()>& task, TaskPriority priority)
            :Task<Y>(task, priority), m_result()
        {
            //empty
        }
        TemplatedTask(const TemplatedTask& other)
        :Task<Y>(other), m_result(other.m_result)
        {
            //empty
        }

        TemplatedTask& operator=(const TemplatedTask& other)
        {
            if (this != &other)
            {
                Task<Y>::operator=(other);
                m_result = other.m_result;
            }
            return *this;
        }
        
        ~TemplatedTask() noexcept
        {
            //empty
        }

        void operator()()
        {
            m_result = Task<Y>::m_task();
            Task<Y>::m_is_valid = true;
            Task<Y>::m_cond_has_res.notify_one();
        }

    private:
        friend class Future<Y>;
        Y m_result;
    };
    




private:
    
    friend void ThreadTask(ThreadPool &tp, size_t index);

    class Thread
    {
        friend class ThreadPool;
    public:
        explicit Thread(ThreadPool& tp, size_t index)
            :m_trd(ThreadTask, std::ref(tp),index),m_index(index)
        {
            //empty
        }
        Thread(const Thread& other) = delete;
        Thread& operator=(const Thread&) = delete;
        ~Thread() noexcept
        {
            m_trd.join();
        }

    private:
        std::thread m_trd;
        size_t m_index;
    };
};
/*<-------------------------------------------------------------------------->*/

template <typename Y>
class Future
{
public:
    Future(std::shared_ptr<ThreadPool::TemplatedTask<Y>> task);
    Future(const Future&);
    Future& operator=(const Future&);
    ~Future() noexcept;

    Y& Get();
    bool IsReady() const;
    void Wait();

private:
    std::shared_ptr<ThreadPool::TemplatedTask<Y>> m_ptr;
    bool m_is_ready;
    Y *m_result;
};



template <typename Y>
Future<Y>::Future(std::shared_ptr<ThreadPool::TemplatedTask<Y>> task)
    :m_ptr(task), m_is_ready(false), m_result(nullptr)
{
    //empty
}


template <typename Y>
Future<Y>::~Future() noexcept
{
    //empty
}


template <typename Y>
Future<Y>::Future(const Future& other)
    :m_ptr(other.m_ptr), m_is_ready(other.m_is_ready), m_result(other.m_result)
{
    //empty
}


template <typename Y>
Future<Y>& Future<Y>::operator=(const Future& other)
{
    if (this != &other)
    {
        m_ptr = other.m_ptr;
        m_is_ready = other.m_is_ready;
    }
    return *this;
}

 
template <typename Y>
Y& Future<Y>::Get()
{
    return GetRes(*m_ptr);
}

template <typename Y>
bool Future<Y>::IsReady() const
{
    return m_is_ready;
}

template <typename Y>
void Future<Y>::Wait()
{
    if (!m_is_ready)
    {
        m_ptr->m_cond_has_res.wait(m_ptr->m_mutex);
        m_is_ready = true;
    }
}


template <typename Y>
Y& GetRes(ThreadPool::TemplatedTask<Y>& task)
{
    std::unique_lock<std::mutex> lock(task.m_mutex);
    while(!task.m_is_valid)
    {
        task.m_cond_has_res.wait(lock);
    }
    return task.m_result;
}
/*<-------------------------------------------------------------------------->*/


template <typename Y>
Future<Y> ThreadPool::AddTask(const std::function<Y()>& task, TaskPriority priority)
{
    std::shared_ptr<ThreadPool::TemplatedTask<Y>> task_ = std::make_shared<ThreadPool::TemplatedTask<Y>>(task, priority);
    m_wqueue.Push(task_);
    Future<Y> future(task_);
    
    return future;
}



} // namespace pirates_speed
