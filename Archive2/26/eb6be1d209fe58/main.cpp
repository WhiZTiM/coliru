template <bool...>
constexpr bool all_true = true;

template <bool B, bool... Bs>
constexpr bool all_true<B, Bs...> = B && all_true<Bs...>;


#include <iostream>
int main()
{
    std::cout << all_true<true, true, false> << std::endl;
    std::cout << all_true<true, true, true> << std::endl;
}
