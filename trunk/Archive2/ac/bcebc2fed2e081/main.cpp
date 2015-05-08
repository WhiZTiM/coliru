#include <iostream>
#include <type_traits>

template<bool b, class T=void>
using enable_if_t=typename std::enable_if<b,T>::type;
template<class...>struct voider{using type=void;};
namespace std { // Emulate void_t of c++1z
  template<class...Ts>using void_t=typename voider<Ts...>::type;
}

template<class...>struct types{using type=types;};
namespace details {
  template<template<class...>class Z, class types, class=void>
  struct test_apply:std::false_type{};
  template<template<class...>class Z, class...Ts>
  struct test_apply<Z,types<Ts...>,std::void_t<Z<Ts...>>>:
    std::true_type
  {};
}

template<template<class...>class Z, class...Ts>
using test_apply=details::test_apply<Z,types<Ts...>>;

template<class X>
using cout_result = decltype( std::cout << std::declval<X>() );

template<class X>
using can_cout_stream = test_apply< cout_result, X >;

template<class T>
std::enable_if_t<!can_cout_stream<const T&>{}>
f(const T& x) {
    std::cout << "Blubb" << std::endl;
}

int main(int, char **) {
    // f(1); // Not okay, gives a compiler error.
    struct A {} a;
    f(a); // Okay, outputs "Blubb"
    return 0;
}