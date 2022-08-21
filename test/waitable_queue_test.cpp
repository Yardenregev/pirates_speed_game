#include "../include/waitable_queue.hpp"
#include "../include/answer.hpp"
#include <iostream>/*std cout cin*/
using namespace pirates_speed;

int main ()
{
    WaitableQueue<std::shared_ptr<Answer>> queue;
    std::shared_ptr<Answer> answer = std::make_shared<Answer>("John", "Sail");
    queue.Push(answer);
    std::shared_ptr<Answer> answer2 = std::make_shared<Answer>("John", "Defend");
    queue.Push(answer2);
    queue.Pop(answer);
    std::cout << answer->GetAnswer() << std::endl;
    queue.Pop(answer);
    std::cout << answer->GetAnswer() << std::endl;





    return 0;
}
