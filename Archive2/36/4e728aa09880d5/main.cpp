#include <type_traits>
#include <iostream>

struct A {
  using type = int;
  void operator[](int);
};

class B { };

namespace details {
  template<class...>struct voider{using type=void;};
  template<class...Ts>using void_t=typename voider<Ts...>::type;

  template<template<class...>class Z, class, class...Ts>
  struct can_apply:
    std::false_type
  {};
  template<template<class...>class Z, class...Ts>
  struct can_apply<Z, void_t<Z<Ts...>>, Ts...>:
    std::true_type
  {};
}
template<template<class...>class Z, class...Ts>
using can_apply=details::can_apply<Z,void,Ts...>;

template <class T, class Index>
using subscript_t = decltype(std::declval<T>()[std::declval<Index>()]);

template <class T, class Index>
constexpr bool has_subscript_v = can_apply<subscript_t, T, Index>::value;

int main() {
  std::cerr << has_subscript_v<A, int>;
  std::cerr << has_subscript_v<B, int>;
}