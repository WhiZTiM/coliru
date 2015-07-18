#include <utility>
#include <type_traits>
#include <iostream>

template <std::size_t ...Ints>
int test(std::index_sequence<Ints...> i)
{
    return sizeof...(Ints);
}
template <typename ...Args>
void foo()
{
    using indices = std::index_sequence_for<Args...>;
    std::cout << test(indices()) << std::endl;
}

int main()
{
     foo<int, float, char>();
}