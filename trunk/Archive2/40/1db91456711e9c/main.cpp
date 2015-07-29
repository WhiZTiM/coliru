#include <array>

constexpr std::array<int, 1> array{{3}};
constexpr int a = array[0];  // Works in >=C++14 but not in C++11

constexpr int b = static_cast<std::array<int, 1> const>(std::array<int, 1>{{3}})[0];

#include <iostream>

int main()
{
    std::cout << a << ' ' << b << '\n';
}
