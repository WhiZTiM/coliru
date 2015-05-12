#include <iostream>

template <typename T>
struct C
{
    typedef T my_type;
};

template <typename T> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

int main()
{
    C<int> c;

    auto f = [&c]()
    {
        decltype(c)::my_type v2; (void)v2;       
        TD<decltype(c)>();
    };
    f();
}
