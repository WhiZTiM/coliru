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

template <typename T>
void specialized(T t, true_type)
{
    std::cout << "is_integral\n";
}

template <typename T>
void specialized(T t, false_type)
{
    std::cout << "!is_integral\n";
}

template <typename T>
void dispatch(T t)
{
    specialized(t, is_integral<T>{});
	//             ~~~~~~~~~~~~~~~^ - przyjmie postać klasy dziedziczącej po true_type lub false_type
}

int main()
{
    dispatch(1);
    dispatch("test");
}
