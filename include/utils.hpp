#include <iostream>

namespace pirates_speed
{
class Utils{
    public:
    Utils() = delete;
    static void ClearInputBuffer()
    {
        if (std::cin.peek() == '\n') {
            std::cin.ignore();
        }
    }
};
}