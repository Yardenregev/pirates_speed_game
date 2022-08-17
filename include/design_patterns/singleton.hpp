#pragma once

namespace pirates_speed
{
template <typename T, typename ...Args>
class Singleton
{
    class GarbageCollector;
    public:
        explicit Singleton() = delete;
        ~Singleton() = delete;
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;


        static T& GetInstance(Args...args);

    private:
        static T* m_instance;
        static GarbageCollector gc;

    private:
        class GarbageCollector
        {
        public:
            GarbageCollector() = default;
            ~GarbageCollector();
        };
};

template <typename T, typename ...Args>
T* Singleton<T, Args...>::m_instance = nullptr;

template <typename T, typename ...Args>
typename Singleton<T, Args...>::GarbageCollector Singleton<T, Args...>::gc;

template <typename T, typename ...Args>
T& Singleton<T, Args...>::GetInstance(Args...args)
{
    if (m_instance == nullptr)
    {
        m_instance = new T(args...);
        static_cast<void>(gc);
    }
    return *m_instance;
}

template <typename T, typename ...Args>
Singleton<T, Args...>::GarbageCollector::~GarbageCollector()
{
    if (Singleton<T, Args...>::m_instance != nullptr)
    {
        delete Singleton<T, Args...>::m_instance;
    }
}


} // namespace pirates_speed