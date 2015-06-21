#include <type_traits>
#include <typeinfo>
#include <iostream>

template<typename T>
struct bar {};

template <typename funT>
void foo(funT function_to_call) {
  auto data = bar<typename std::result_of<decltype(function_to_call)&()>::type>();
  (void) data;
  std::cout << typeid(typename std::result_of<decltype(function_to_call)&()>::type).name() << std::endl;
}

int fun() {
  return 100;
}

int main() {
  foo(fun);
}