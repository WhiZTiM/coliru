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
struct A
{
    static_assert(is_integral<T>::value, "Typ T musi byc typem calkowitoliczbowym!");
};

int main()
{
    A<int> a; // OK
    A<double> b; // Błąd!
}
