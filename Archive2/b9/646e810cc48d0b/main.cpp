#include <tuple>

using uint = unsigned int;

template <typename T>
struct function_traits;

template <typename R, typename ... Args>
struct function_traits<R(Args...)>
{
    using return_t = R;

	static const uint args_count = sizeof...(Args);

	template <uint i>
	struct arg
	{
		using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
	};
};

template <typename R, typename ... Args>
struct function_traits<R(*)(Args...)>
{
	using return_t = R;

	static const uint args_count = sizeof...(Args);

	template <uint i>
	struct arg
	{
		using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
	};
};

template <typename R, typename C, typename ... Args>
struct function_traits<R(C::*)(Args...)>
{
	using return_t = R;
	using class_t = C;

	static const uint args_count = sizeof...(Args);

	template <uint i>
	struct arg
	{
		using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
	};
};

template <typename T>
using return_t = typename function_traits<T>::return_t;

template <typename T>
using class_t = typename function_traits<T>::class_t;

template <typename T, uint i>
using arg_t = typename function_traits<T>::arg<i>::type;