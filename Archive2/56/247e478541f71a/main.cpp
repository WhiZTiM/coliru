#include <cstddef>
#include <vector>

struct foo
{
    int i = 123;
} f;

struct bar
{
    int j = 456;
} b;

template<typename T>
struct some_expression_thingy
{
    auto times(std::size_t t)
    {
        return std::vector<T>(t, T{});
    }
};

template<typename T>
auto select(const T &)
{
    return some_expression_thingy<T>{};
}

#include <iostream>

int main()
{
    for (const auto & ref : select(f).times(2))
    {
        std::cout << ref.i << std::endl;
    }
    
    for (const auto & ref : select(b).times(3))
    {
        std::cout << ref.j << std::endl;
    }
}
