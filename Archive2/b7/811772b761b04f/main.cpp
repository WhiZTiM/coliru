#include <tuple>
#include <utility>
#include <type_traits>
#include <initializer_list>

template <std::size_t From, size_t... indices, typename T1, typename T2, typename Func>
void transform(T1&& s, T2& t, Func f, std::index_sequence<indices...>)
{
    (void)std::initializer_list<int>{
        (std::get<indices+From>(t) = f(std::get<indices>(std::forward<T1>(s))), 0)...};  
}


template <std::size_t From, std::size_t To, typename T1, typename T2, typename Func>
void transform(T1&& s, T2& t, Func f)
{
    transform<From>(std::forward<T1>(s), t, f, std::make_index_sequence<To-From+1>());
}

#include <iostream>
int main() {
    std::tuple<int, int, int> t;
    transform<1,2>(std::make_tuple(1,2,3), t, [] (auto i) {std::cout << i; return -i;});
}