#include <iostream>

template <typename T>
struct integral_type_info;

template <>
struct integral_type_info<int>
{
    static constexpr int bits = 32;
	static constexpr bool is_signed = true;
};

template <>
struct integral_type_info<unsigned long long>
{
	static constexpr int bits = 64;
	static constexpr bool is_signed = false;
};

template <typename T>
void foo(T)
{
    std::cout << integral_type_info<T>::bits << std::endl;
	std::cout << integral_type_info<T>::is_signed << std::endl;
}

int main()
{
    foo(100);
    foo(100000000000000ULL);
}
