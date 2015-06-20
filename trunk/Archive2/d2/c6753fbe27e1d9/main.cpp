#include <iostream>

template<typename T>
T f(T&& a, T&& b)
{
    a = std::forward<T>(a) + std::forward<T>(b);
    return c;
}


int main()
{
    
}