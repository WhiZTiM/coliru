#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include <sstream>
#include <type_traits>

template<class...>struct voider{using type=void;};
template<class...Ts>using void_t=typename voider<Ts...>::type;

template<class T> 
struct type { };

template<class... Ts>
struct dup_helper : type<Ts>... { };

namespace details {
  template<template<class...>class Z, class, class...>
  struct can_apply:std::false_type{};
  template<template<class...>class Z, class...Ts>
  struct can_apply<Z, void_t<Z<Ts...>>, Ts...>:
    std::true_type{};
}
template<template<class...>class Z, class...Ts>
using can_apply=details::can_apply<Z, void, Ts...>;

template<class...Ts>
using no_dupes = can_apply< dup_helper, Ts... >;

int main() {
    std::cout << no_dupes<int, float>{} << no_dupes<float, float>{} << '\n'; 
}