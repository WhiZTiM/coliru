#include <algorithm>
#include <iostream>
#include <vector>


template<typename C>
std::ostream& operator<<(std::ostream& os, const C & c)
{
    for (auto i : c)
    {
        std::operator<<(os, i);
    }
    return os;
}

int main()
{
    std::vector<int> vec = { 1, 2, 3, 4};
    std::cout << vec << std::endl;
}