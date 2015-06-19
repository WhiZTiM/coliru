template <bool... Bs>
constexpr bool all_true = (Bs && ...);

#include <iostream>
int main()
{
    std::cout << all_true<true, true, false> << std::endl;
    std::cout << all_true<true, true, true> << std::endl;
}
