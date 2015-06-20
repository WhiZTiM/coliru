#include <iostream>

template<typename T>
T f(const T& a, const T& b) // Overload 1
{
    T c(a + b);
    return c;
}

template<typename T>
T f(T&& a, const T& b) // Overload 2
{
    a = (a + b);
    return a;
}

template<typename T>
T f(const T& a, T&& b) // Overload 3
{
    b = (a + b);
    return b;
}

template<typename T>
T f(T&& a, T&& b) // Overload 4
{
    a  = (a + b);
    return a;
}


int main()
{
    
}