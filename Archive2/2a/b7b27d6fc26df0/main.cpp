#include <iostream>
#include <vector>
#include <array>
#include <cstddef>
#include <utility>
#include <type_traits>

template <typename It, typename Func>
struct to_array_t
{
    It first;
    
    Func func;
    
    template <typename F>
    to_array_t(It first, F&& func) : first(first), func(std::forward<F>(func)) {}
    
    template <typename T, std::size_t N>
    operator std::array<T, N>()
    {
        return to_array<T, N>(std::make_index_sequence<N>{});
    }
    
    template <typename T, std::size_t N, std::size_t... Is>
    std::array<T, N> to_array(std::index_sequence<Is...>)
    {
        return { func(*(first + Is))... };
    }
};

template <typename It, typename Func>
to_array_t<It, typename std::decay<Func>::type> to_array(It first, Func&& func)
{
    return { first, std::forward<Func>(func) };
}

struct Bar
{
    int m_1, m_2;
    Bar(int a, int b) : m_1(a), m_2(b) {}
};

struct Foo
{
    int m_1, m_2;
    Foo(int a, int b) : m_1(a), m_2(b) {}
};

int main()
{
    std::vector<Foo> foos{ {1, 2}, {3, 4} };
    
    std::array<Bar, 2> bars = to_array(foos.begin(), [](Foo foo){
        return Bar(foo.m_1, foo.m_2);
    });
    
    for (auto& bar : bars)
    {
        std::cout << bar.m_1 << " " << bar.m_2 << std::endl;
    }
}
