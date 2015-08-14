#include <iostream>
#include <limits>

auto a = std::numeric_limits<long>::min();

int main(int ,char**)
{
    std::cout << static_cast<unsigned short>((short)-32768) << '\n';
    std::cout << -static_cast<unsigned short>((short)-32768) << '\n';
}
