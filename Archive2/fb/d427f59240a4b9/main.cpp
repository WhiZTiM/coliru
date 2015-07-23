#include <type_traits>

template<typename Condition>
using EnableIf = std::enable_if_t<Condition::value, int>;

template<
    typename T,
	EnableIf<std::is_trivially_constructible<T>>...,
	EnableIf<std::is_trivially_destructible<T>>...
>
void Test(T t) {}
/* main.cpp(11): error C3547: template parameter 'unnamed-parameter' cannot 
 *               be used because it follows a template parameter pack and
 *               cannot be deduced from the function parameters of 'Test'
 */
 
struct foo
{
	foo() {}
	~foo() {}
};

int main()
{
	Test(foo{});
}
