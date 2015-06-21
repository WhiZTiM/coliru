#include <type_traits>
#include <functional>
#include <typeinfo>
#include <iostream>

template<typename T>
struct bar {};

template <typename funT, typename ...Args>
void foo(funT function_to_call, Args... args) {
  auto data = bar<decltype(function_to_call(std::forward<Args>(args)...))>();
  (void) data;
  std::cout << typeid(typename std::result_of<funT(Args...)>::type).name() << std::endl;
  std::cout << typeid(decltype(function_to_call(std::forward<Args>(args)...))).name() << "\n";
}

int fun1() {
  return 100;
}

double fun2(double a, double b) {
  return 1.0;
}

int main() {
  foo(fun1);
  foo(fun2, 1, 2);
}