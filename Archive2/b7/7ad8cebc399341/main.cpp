#include <iostream>
#include <type_traits>

template <typename T, bool = std::is_enum<T>::value>
struct H{};

template <typename T>
struct H<T, true> {
using type = typename std::underlying_type<T>::type;
};

template <typename T>
struct H<T, false> {
using type = T;
};

template <typename T, typename = typename std::enable_if<std::is_enum<T>::value || std::is_integral<T>::value>::type>
struct S {  
  using underlying = typename H<T>::type;
};

enum E1 {};
enum E2 : unsigned {};
class C {};

void f() {
  S<unsigned> s1;
  S<E1> s2;
  S<E2> s3;
  //S<float> s4; // Uncomment to test failure
  //S<C> s5; // Uncomment to test failure
}

int main() {
  f();
}
