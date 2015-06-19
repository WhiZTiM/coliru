#include <iostream>
struct true_type
{
    static constexpr bool value = true;
};

struct false_type
{
	static constexpr bool value = false;
};

template <typename T>
struct is_pointer : false_type {};

template <typename T>
struct is_pointer<T*> : true_type {};

int main()
{
    std::cout << is_pointer<int>::value << std::endl;
    std::cout << is_pointer<int*>::value << std::endl;
}
