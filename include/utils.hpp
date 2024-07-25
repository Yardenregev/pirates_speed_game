#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>

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

    static std::string ToLowerCase(const std::string& input)
    {
        std::string output = input;
        std::transform(output.begin(), output.end(), output.begin(), [](unsigned char c){ return std::tolower(c); });
        return output;
    }

};
}