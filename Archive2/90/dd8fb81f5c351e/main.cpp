#include <iostream>
#include <limits>

auto a = std::numeric_limits<long>::min();

int main(int ,char**)
{
    unsigned int notOne = static_cast<unsigned int>(-1);
    std::cerr << notOne << std::endl;
    unsigned int one = -static_cast<unsigned int>(-1);
    std::cerr << one << std::endl;
    unsigned int absMin = static_cast<unsigned int>(std::numeric_limits<int>::min());
    std::cerr << absMin << std::endl;

}
