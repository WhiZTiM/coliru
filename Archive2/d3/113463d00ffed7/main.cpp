#include <utility>
#include <tuple>
#include <type_traits>
#include <iostream>

template <std::size_t ...Ints>
int test(std::index_sequence<Ints...> i)
{
    return sizeof...(Ints);
}

template<class... T>
using index_sequence_for = std::make_index_sequence<sizeof...(T)>;

template <typename ...Args>
void foo()
{
    using indices1 = std::index_sequence_for<Args...>;
    using indices2 = index_sequence_for<Args...>;
    using indices3 = std::make_index_sequence<sizeof...(Args)>;
    std::cout << test(indices1()) << std::endl;
    std::cout << test(indices2()) << std::endl;
    std::cout << test(indices3()) << std::endl;
}

int main()
{
     foo<int, float, char>();
}