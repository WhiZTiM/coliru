#include <utility>

template<typename T> struct remove_class_ref { };
template<typename C, typename R, typename... A>
struct remove_class_ref<R(C::*)(A...)> { using type = R(*&)(A...); };
template<typename C, typename R, typename... A>
struct remove_class_ref<R(C::*)(A...) const> { using type = R(*&)(A...); };
template<typename C, typename R, typename... A>
struct remove_class_ref<R(C::*)(A...) volatile> { using type = R(*&)(A...); };
template<typename C, typename R, typename... A>
struct remove_class_ref<R(C::*)(A...) const volatile> { using type = R(*&)(A...); };

template <class C>
struct call_lambda_i
{
    //[...]
	typedef typename remove_class_ref<decltype(&C::operator())>::type fun_ref_t;
	static const bool is_static = std::is_assignable<fun_ref_t, C>::value;
	//[...]
};

int main()
{
	auto x = []{ return 5; };
	auto y = [x]{ return x(); };

	static_assert(call_lambda_i<decltype(x)>::is_static, "non-catpure should convert");
	static_assert(!call_lambda_i<decltype(y)>::is_static, "catpure should not convert");
}
