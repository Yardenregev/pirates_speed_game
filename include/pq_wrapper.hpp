#pragma once

#include <queue> // std::priority_queue

namespace pirates_speed
{
template <typename T>
class PQ: private std::priority_queue<T>
{
public:
    using std::priority_queue<T>::pop;
    using std::priority_queue<T>::empty;
    using std::priority_queue<T>::push;

    const T& front(){ return std::priority_queue<T>::top(); }
};

} //end namespace pirates_speed