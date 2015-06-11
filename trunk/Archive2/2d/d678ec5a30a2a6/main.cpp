#include <iostream>
#include <utility>

template <typename T>
void g(T&&)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    auto f = [](auto&& v)
    {
        g(std::forward<decltype(v)>(v));
        //             ~~~~~~~~~~^
    };
    
    f(1);
    int a{};
    f(a);
}
