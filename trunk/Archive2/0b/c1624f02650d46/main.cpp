#include <tuple>
#include <iostream>

template< typename ...T, std::size_t... I>
void print_impl(std::tuple<T...> t, std::index_sequence<I...>)
{
    (std::cout << ... << std::get<I>(t));
}

template<typename ...T>
void print(std::tuple<T...> t)
{
    print_impl(t, std::make_index_sequence<sizeof...(T)>());
}

int main()
{
print(std::make_tuple(1, 2, 3, 4));
return 0;
}
