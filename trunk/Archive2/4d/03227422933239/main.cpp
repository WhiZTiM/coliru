#include <iostream>
#include <tuple>
 #include <vector>
 
struct A { explicit A(int) {} A(const A&) = default; };

template <typename T> struct B { explicit B(const std::initializer_list<T>&) {} B(const B&) = default; }; 
 

template <typename... Args>
struct converter
{
    std::tuple<Args...> _args;
 
	converter(Args&&... args) : _args(std::forward_as_tuple(std::forward<Args>(args)...)) {}
 
	template <typename T>
	operator T() { return T(std::get<Args>(_args)...); }
};
 
template <typename... Args>
auto initializer(Args&&... args)
{
    return converter<Args...>(std::forward<Args>(args)...);
}

template <typename Arg>
auto initializer(const std::initializer_list<Arg>& list)
{
    return converter<decltype(list)>(list);
}

A foo()
{
    return initializer(4);
}

B<int> bar()
{
    return initializer({1,2,3});
}

int main() 
{
    A a = foo();
    B<int> b = bar();
    return 0;
}