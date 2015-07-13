#include <iostream>
#include <type_traits>
#include <cxxabi.h>
#include <typeinfo>

template <typename T>
const char * type_name()
{
    return abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
}

template <typename...>
struct vargs {};
 
template <typename T>
struct outer
{
    template <typename>
	struct inner;
 
	template <typename... Args>
	struct inner<vargs<Args...>>
	{
		using result = std::true_type;
	};
 
	template <template <typename...> class C, typename... Args>
	struct inner<C<Args...>>
	{
		using result = std::false_type;
	};
};
 
struct eval_tag {};
 
template <typename T>
using eval_t = typename outer<eval_tag>::inner<T>::result;
 
int main() 
{
	std::cout << type_name<eval_t<vargs<int, char, bool>>>() << '\n';
	return 0;
}