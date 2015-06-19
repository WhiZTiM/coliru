template <bool...>
struct all_true
{
    static constexpr bool value = true;
};

template <bool B, bool... Bs>
struct all_true<B, Bs...>
{
	static constexpr bool value = B && all_true<Bs...>::value;
};

#include <iostream>
int main()
{
    std::cout << all_true<true, true, false>::value << std::endl;
    std::cout << all_true<true, true, true>::value << std::endl;
}
