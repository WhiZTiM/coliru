#include <array>
#include <iostream>

template<typename T, std::size_t N>
void foo(T (&&arr)[N])
{
    std::cout << N << '\n';
}

int main()
{
    foo({ 0, 1, 2, 3, 4 });
}
