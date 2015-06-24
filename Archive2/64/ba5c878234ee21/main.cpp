#include <type_traits>

template<class... T> struct inherits :
    std::true_type
{};

template<class T, class Base1, class... Bases>
struct inherits<T, Base1, Bases...> :
	std::conditional_t< std::is_base_of<Base1, T>{},
		inherits<T, Bases...>,
		std::false_type
	>
{};

class A {};
class B {};
class C {};
class Impl : public A, public B, public C {};
class Bad : public C, public B {};

template<class T>
std::enable_if_t<
	inherits<T, A, B, C>{},
	void
> foo(const T& t)
{
}

int main()
{
	foo(Impl{});
    //foo(Bad{}); // Deduction fails
}
