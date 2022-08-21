#include "../include/threadpool.hpp"

namespace pirates_speed
{
void ThreadTask(ThreadPool &tp, size_t index)
{
    while(!tp.m_is_done)
    {
        while(tp.m_is_paused)
        {
            if(tp.m_is_done || tp.m_vec_should_terminate[index])
            {
                return;
            }
        }
        char buffer[100] = {0};
        sprintf(buffer, "Thread %ld\n", index);
        write(1, buffer, strlen(buffer));
        std::unique_lock<std::mutex> lock(tp.m_mutex_can_pop);
        std::shared_ptr<ThreadPool::GeneralTask> task_ = 
                    std::make_shared<ThreadPool::Task<int>>([]{return 0;}, LOW);
        tp.m_wqueue.Pop(task_);
        lock.unlock();
        (*task_)();
    }
}

ThreadPool::ThreadPool(size_t thread_num_)
    :m_num_of_threads(thread_num_), m_vec(), m_wqueue(), m_is_done(false),
     m_is_paused(false), m_mutex_can_pop(), m_vec_should_terminate()
{
    for (size_t i = 0; i < m_num_of_threads; ++i)
    {
        m_vec.push_back(new Thread(std::ref(*this), i));
        m_vec_should_terminate.push_back(false);
    }
}


ThreadPool::~ThreadPool() noexcept
{
    while(!m_wqueue.IsEmpty()) //to wait for remaining tasks to execute
    {
    }
    m_is_done = true;
    PoisonApple(FINISH); // to make threads leave waiting
    
    for (size_t i = 0; i < m_num_of_threads; ++i)
    {
        delete m_vec[i];
    }
}

void ThreadPool::AddTask(const std::function<void()>& task, TaskPriority priority)
{
    std::shared_ptr<ThreadPool::Task<void>> task_ = std::make_shared<ThreadPool::Task<void>>(task, priority);
    m_wqueue.Push(task_);
}



void ThreadPool::ResizePool(size_t new_size)
{
    Pause();
    if(new_size > m_num_of_threads)
    {
        for(size_t i = m_num_of_threads; i < new_size; ++i)
        {
            m_vec.push_back(new Thread(std::ref(*this), i));
        }
        m_num_of_threads = new_size;
    }

    else if(new_size < m_num_of_threads)
    {
        for(size_t i = new_size; i < m_num_of_threads; ++i)
        {
            m_vec_should_terminate[i] = true;
            delete m_vec[i];
        }
        m_vec.resize(new_size);
        m_num_of_threads = new_size;
    }
    assert(new_size == m_vec.size());

   Resume(); 
}

void ThreadPool::Pause()
{
    m_is_paused = true;
    PoisonApple(PAUSE);
}

void ThreadPool::Resume()
{
    m_is_paused = false;
}

void ThreadPool::PoisonApple(TaskPriority p)
{
    for(size_t i = 0; i < m_num_of_threads; ++i)
    {
        AddTask<int>([]{return 0;}, p);
    }
}


} // namespace pirates_speed
