#include <iostream>
#include <functional>
#include <string>

template <typename T>
struct GetType;


int main ()
{
    const auto f = [] (auto&& x)
    {
        GetType<decltype(x)> _x; // string&&
        GetType<decltype((x))> _y; // string& *no-longer an x-value!*
    };
    f (std::string ("foo"));
}
    
