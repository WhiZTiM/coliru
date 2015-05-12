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
    const char * data = "ab\0\0cd";
    std::vector<char> vec(data, data + 6);
    std::cout << vec << std::endl;
    std::cout << "size: " << vec.size() << std::endl;
}
