#include <iostream>
#include <string>
#include <vector>

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
    const char * data = "abcd";
    std::vector<char> data(data, data + 4);
    std::cout << data << std::endl;
}
