#include <iostream>

struct true_type
{
    static constexpr bool value = true;
};

struct false_type
{
	static constexpr bool value = false;
};

template <typename T> struct is_integral : false_type {};
template <> struct is_integral<int> : true_type {};
template <> struct is_integral<short> : true_type {};
template <> struct is_integral<long> : true_type {};

template <bool B, typename T = void>
struct enable_if
{
    using type = T;
};

template <typename T>
struct enable_if<false, T> {};

template <typename T>
typename enable_if<is_integral<T>::value>::type foo(T)
{
    std::cout << "is_integral\n";
}

template <typename T>
typename enable_if<!is_integral<T>::value>::type foo(T)
{
    std::cout << "!is_integral\n";
}

int main()
{
    foo(1);
    foo("test");
}
