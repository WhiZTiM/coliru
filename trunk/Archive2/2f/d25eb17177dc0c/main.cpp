#include <iostream>

template<typename Func, typename... Args>
auto curry(Func func, Args... args)
{
    return [func = std::forward<Func> (func), args = std::forward<Args>(args)...](auto... x)
    {
        return func(args..., x...);
    };
}

struct foo
{
    void operator () (int x, int y, int z) const
    {
        std::cout << x << "," << y << "," << z << std::endl;
    }
};

int main ()
{
    auto f = curry(foo (), 1);
    f(2, 3);
}
