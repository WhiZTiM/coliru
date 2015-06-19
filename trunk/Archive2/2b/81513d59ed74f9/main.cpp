template <bool B1, bool B2 = true, bool B3 = true, bool B4 = true, bool B5 = true>
struct all_true
{
    static const bool value = B1 && B2 && B3 && B3 && B4 && B5;
};

#include <iostream>
int main()
{
    std::cout << all_true<true, true, false>::value << std::endl;
    std::cout << all_true<true, true, true>::value << std::endl;
}
