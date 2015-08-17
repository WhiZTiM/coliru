#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include <sstream>
#include <type_traits>
#include <memory>

template<class T>struct tag{using type=T;};
template<class Tag>using type_t=typename Tag::type;

template<template<class...>class> struct Z {};
template<class Z, class...Ts>
struct apply {};
template<template<class...>class z, class...ts>
struct apply< Z<z>, ts... >:
  tag< z<ts...> >
{};
template<class Z, class...Ts>
using apply_t = type_t< apply<Z, Ts...> >;

template<class z, class... Ts>
struct Bind {
  template<class... More>
  using type_base = apply_t< z, Ts..., More... >;
  using type = Z<type_base>;
};
template<class Z, class...Ts>
using Bind_t = type_t<Bind<Z,Ts...>>; // strip ::type
using Bind_z = Z<Bind_t>; // quote into a Z<?>

template<class...>struct types{using type=types;};
using types_z = Z<types>;

template<class...Ts>
using prefix = apply_t< Bind_z, types_z, Ts... >;
using prefix_z = Z<prefix>;

int main() {
    apply_t< apply_t< prefix_z, int, double, char >, std::string > test = types<int, double, char, std::string>{};
    (void)test;
}