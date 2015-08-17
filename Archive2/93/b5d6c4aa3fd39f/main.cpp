#include <type_traits>

template <typename T>
struct identity { using type = T; };

template <typename...>
using void_t = void;

template <typename F>
struct call_operator;

template <typename C, typename R, typename... A>
struct call_operator<R(C::*)(A...)> : identity<R(A...)> {};

template <typename C, typename R, typename... A>
struct call_operator<R(C::*)(A...) const> : identity<R(A...)> {};

template <typename C, typename R, typename... A>
struct call_operator<R(C::*)(A...) volatile> : identity<R(A...)> {};

template <typename C, typename R, typename... A>
struct call_operator<R(C::*)(A...) const volatile> : identity<R(A...)> {};

template <typename F>
using call_operator_t = typename call_operator<F>::type;

template <typename, typename = void_t<>>
struct is_convertible_to_function
    : std::false_type {};

template <typename L>
struct is_convertible_to_function<L, void_t<decltype(&L::operator())>>
    : std::is_assignable<call_operator_t<decltype(&L::operator())>*&, L> {};

int main()
{
	auto x = [] { return 5; };
	auto y = [x] { return x(); };
    
    static_assert(is_convertible_to_function<decltype(x)>::value, "!");
	static_assert(!is_convertible_to_function<decltype(y)>::value, "!");
}
