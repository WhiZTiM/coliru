#include <iostream>
#include <cmath>
#include <typeinfo>
 
template<class T, class U>
auto add(T t, U u) -> decltype(t + u) // the return type is the type of operator+(T,U)
{
    return t + u;
}
 
auto get_fun(int arg)->double(*)(double) // same as double (*get_fun(int))(double)
{
    switch (arg) {
        case 1: return std::fabs;
        case 2: return std::sin;
        default: return std::cos;
    }
}
 
int main()
{
    
    int x = 45;
    int & y = x;
    auto z = y;
    z = 32;
    std::cout << z << " " << y << " " << x;
}