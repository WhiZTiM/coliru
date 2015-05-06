#include <type_traits>
#include <iostream>

template<typename, typename, typename=void>
struct has_cout
    : std::false_type {};

template<typename stream_t, typename T>
struct has_cout<T, decltype(std::declval<stream_t>()<<std::declval<T>(),void())>
    : std::true_type {};

template<typename stream_t, typename T>
auto f(stream_t &s, const T& x) 
  -> typename std::enable_if<!has_cout<stream_t, T>::value>::type
{
    s << "Huhu" << std::endl;
}
  
struct A {};

int main()
{
    f(std::cout, 1); // not OK that this is okay.
    A a;
    f(std::cout, a); // OK
}
