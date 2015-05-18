#include <iostream>
#include <algorithm>
#include <utility>
#include <tuple>


int main()
{
    int b[5];
    std::tie(b[0], b[1], b[2], b[3], b[4]) = std::make_tuple(4, 3, 2, 1, 0);
    for(const auto& c : b)
        std::cout<< c << ' ';
}
