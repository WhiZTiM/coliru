#include <tuple>
#include <utility>
#include <type_traits>
#include <initializer_list>

template <size_t... indices, typename T1, typename T2, typename Func>
void transform(T1&& s, T2& t, Func f,
               std::index_sequence<indices...>)
{
    (void)std::initializer_list<int>{(std::get<indices>(t) =  f(std::get<indices>(s)),0)...};  
}


template <typename T1, typename T2, typename Func>
void transform(T1&& s, T2& t, Func f)
{
    transform(std::forward<T1>(s), t, f, 
              std::make_index_sequence<std::tuple_size<std::decay_t<T1>>{}>());
}

#include <iostream>
int main() {
    std::tuple<int, int, int> t;
    transform(std::make_tuple(1,2,3), t, [] (auto i) {std::cout << i; return -i;});
}