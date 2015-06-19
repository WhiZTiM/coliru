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

template <bool B>
struct A
{
    template <typename T>
	static void specialized(T t)
	{
    std::cout << "!is_integral\n";
	}
};

template <>
struct A<true>
{
	template <typename T>
	static void specialized(T t)
	{
        std::cout << "is_integral\n";
	}
};

template <typename T>
void dispatch(T t)
{
	A< is_integral<T>::value >::specialized(t);
	// ~~~~~~~~~~~~~~~~~~~~^ - warunek przyjmie wartość true lub false, co oddeleguje wywołanie do jednej z klas
}

int main()
{
    dispatch(1);
    dispatch("test");
}
