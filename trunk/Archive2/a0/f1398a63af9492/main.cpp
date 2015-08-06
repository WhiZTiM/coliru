#include <iostream>

template<typename Func, typename... Args>
auto curry(Func func, Args... args)
{
    return [=](auto... x)
    {
        return func(args..., x...);
    };
}

void foo(int x, int y, int z)
{
    std::cout << x << "," << y << "," << z << std::endl;
}

int main ()
{
    auto f = curry(foo, 1);
    f(2, 3);
}
