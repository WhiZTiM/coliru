#include <utility>
#include <array>
#include <iostream>

template<typename... T>
using xxx = std::array<size_t,sizeof...(T)>;

template <typename ...Args>
void foo()
{
    xxx<Args...> x;
    std::cout << x.size() << std::endl;
}

int main()
{
     foo<int, float, char>();
}