#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
    std::cout << words << std::endl;
    
    std::vector<int> arr={15,5,6,55,44};
    std::sort(arr);
    
    for (auto& v : arr)
        printf("%d\n", v);
    
}
