#include <iostream>
#include <string>
#include <vector>
#include <limits>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << static_cast<unsigned short>(std::numeric_limits<int>::max()) << std::endl;
}
