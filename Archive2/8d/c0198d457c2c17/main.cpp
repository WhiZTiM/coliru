#include <iostream>

void foo(int x, char y, bool z)
{
    std::cout << x << y << z << '\n';
}

template <typename F>
void bar(F f)
{
    f(1, '2', true);
}

int main()
{
    bar<decltype(foo)>(foo);
}