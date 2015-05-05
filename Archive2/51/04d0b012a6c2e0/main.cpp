#include <type_traits>
#include <iostream>

template<typename, typename=void>
struct has_cout
    : std::false_type {};

template<typename T>
struct has_cout<T, decltype(std::cout<<std::declval<T>(),void())>
    : std::true_type {};

template<typename T>
auto f(const T& x) 
  -> typename std::enable_if<!has_cout<T>::value>::type
{
    std::cout << "Huhu" << std::endl;
}
  
struct A {};

int main()
{
    // f(1); // not OK
    A a;
    f(a); // OK
}
