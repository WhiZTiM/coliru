#include <type_traits>

constexpr int int_from_string(char const* str)
{
    int result = 0;
    for(;*str;++str)
    {
        result = result*10 + *str-'0';
    }
    return result;
}
template<char... cs>
constexpr int int_from_string()
{
    constexpr char str[] = {cs..., '\0'};
    return int_from_string(str);
}

template<char... cs>
constexpr auto operator "" _ci()
{
    return std::integral_constant<int, int_from_string<cs...>()>{};
}

#include <iostream>
template<typename T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main()
{
    print_type<decltype(0_ci)>();
    print_type<decltype(15_ci)>();
}