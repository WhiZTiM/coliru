#include <type_traits>
#include <utility>
#include <cstddef>

namespace helper
{
    template<typename Modify, typename Apply, std::size_t... Is, typename... Args>
    decltype(auto) modify_n_and_apply(Modify m, Apply a, std::size_t N, std::index_sequence<Is...>, Args&&... args)
    {
        return a((Is == N ? m(std::forward<Args>(args)) : std::forward<Args>(args))...);
    }
}

template<typename Modify, typename Apply, typename... Args>
decltype(auto) modify_n_and_apply(Modify m, Apply a, std::size_t N, Args&&... args)
{
    return helper::modify_n_and_apply(m, a, N, std::index_sequence_for<Args...>{}, std::forward<Args>(args)...);
}


#include <iostream>

int main()
{
    auto apply = [](auto&&... args) { int _ [] = {(std::cout << args << " ", 0)..., 0}; (void)_; };
    auto modify = [](auto arg) { return arg + 42; };
    
    modify_n_and_apply(modify, apply, 2, 0, 1, 2, 3);
}