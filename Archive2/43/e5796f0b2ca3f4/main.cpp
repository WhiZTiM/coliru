#include <iostream>

namespace details {
  template<class...>struct voider{using type=void;};
  template<class...Ts>using void_t=typename voider<Ts...>::type;

  template<template<class...>class Z, class, class...Ts>
  struct can_apply:std::false_type{};
  template<template<class...>class Z, class...Ts>
  struct can_apply<Z, void_t<Z<Ts...>>, Ts...>:std::true_type{};
}
template<template<class...>class Z, class...Ts>
using can_apply=details::can_apply<Z,void,Ts...>;

template <typename X, typename T>
using rebind_t = typename X::template rebind<T>;

template <typename X>
 using has_rebind = can_apply<rebind_t, X, int>;

struct A { };
struct B { template <typename > struct rebind { }; };

int main() {
    std::cout << has_rebind<A>::value << std::endl;
    std::cout << has_rebind<B>::value << std::endl;
}