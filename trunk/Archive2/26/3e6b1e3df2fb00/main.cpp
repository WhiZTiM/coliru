#include <iostream>

template<typename T>
T const& as_const(T& obj)
{
    return obj;
}

int main()
{
    auto a = 42;
    auto l = [&x = as_const(a)] { std::cout << x; };
    l();
}