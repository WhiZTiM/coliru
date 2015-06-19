#include <iostream>

template <typename T>
struct is_pointer
{
    static constexpr bool value = false;
};

template <typename T>
struct is_pointer<T*>
{
	static constexpr bool value = true;
};

int main()
{
    std::cout << is_pointer<int>::value << std::endl;
    std::cout << is_pointer<int*>::value << std::endl;
}
