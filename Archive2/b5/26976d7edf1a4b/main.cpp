#include <iostream>

struct true_type
{
    static constexpr bool value = true;
};

struct false_type
{
	static constexpr bool value = false;
};

template <typename T, typename U>
struct is_same : false_type {};

template <typename T>
struct is_same<T, T> : std::true_type {};

template <typename T>
struct remove_pointer
{
    using type = T;
};

template <typename T>
struct remove_pointer<T*> : remove_pointer<T> {};

int main()
{
    std::cout << is_same<remove_pointer<int********>::type, int>::value << std::endl;
}
