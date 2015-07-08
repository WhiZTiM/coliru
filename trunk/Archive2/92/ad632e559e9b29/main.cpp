#include <iostream>
#include <array>

template <std::size_t N>
using Array = std::array<int, N>;

int main()
{
    Array<3> a{1,2,3};
    for (auto i : a)
        std::cout << i;
}