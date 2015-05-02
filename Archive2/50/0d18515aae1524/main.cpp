#include <iostream>
#include <vector>

namespace N {
    template <typename T>
    struct alice { };
    
    template <typename T>
    std::vector<T> bob(alice<T>, size_t size) {
        return std::vector<T>(size);
    }
    
    template <typename T, typename... Args>
    auto bob(alice<T> a, size_t first, Args... sizes) 
    -> std::vector<decltype(bob(a, sizes...))>
    {
        auto inner = bob(a, sizes...);
        return std::vector<decltype(inner)>(first, inner);
    }
}


template <typename T, typename... Args>
auto make_vector(Args... args)
-> decltype(bob(N::alice<T>{}, args...))
{
    return bob(N::alice<T>{}, args...);
}

int main()
{
    std::size_t n = 5;
    auto x = make_vector<int>(n + 1, n * 2, n * 3, n * 4);
    static_assert(std::is_same<decltype(x), std::vector<std::vector<std::vector<std::vector<int>>>>>::value, "");
}