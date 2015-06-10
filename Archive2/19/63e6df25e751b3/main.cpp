#include <iostream>
#include <memory>

using namespace std;

template < typename D >
class Base
{
public:
    typedef D EType;
};

template<class T>
struct is_Base
{
    using base_type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

	template<class U>
	static constexpr std::true_type test(Base<U> *) { return std::true_type(); }
	static constexpr std::false_type test(...) { return std::false_type(); }

	using type = decltype(test(std::declval<T*>()));
};

template <typename T, typename = typename std::enable_if< is_Base< T >::type::value >::type >
void foo(T const&)
{
}


class Derived : public Base<Derived> {};
class NotDerived {};


int main()
{
    Derived d;
    //NotDerived nd;
    
    foo(d);
    //foo(nd); // <-- Should cause compile error
    
    return 0;
}