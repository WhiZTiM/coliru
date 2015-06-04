

#include <functional>
#include <string>
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <tuple>
struct ulong_ip_tag{};
struct string_ip_tag{};
struct resolved_ip_tag{};
struct invalid_ip_tag{};



template<typename _Type, typename _Handler>
void handler(_Handler, _Type)
{
	std::cout << "other type" << std::endl;
}

template<typename _Handler>
void handler(_Handler, resolved_ip_tag)
{
	std::cout << typeid(resolved_ip_tag).name() << std::endl;
}

template<typename _Handler>
void handler(_Handler, string_ip_tag)
{
	std::cout << typeid(string_ip_tag).name() << std::endl;
}

template<typename _Handler>
void handler(_Handler, ulong_ip_tag)
{
	std::cout << typeid(ulong_ip_tag).name() << std::endl;
}

void real()
{

}
template<typename ..._Args>
struct bind_wrap
{
    constexpr static auto deduce = [](_Args...params){handler(params...);};
    typedef decltype(deduce) type;

};

int main()
{
	bind_wrap<decltype(real),ulong_ip_tag>::deduce(real,ulong_ip_tag());
}

