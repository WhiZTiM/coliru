#include <type_traits>
#include <functional>
#include <typeinfo>
#include <iostream>

template<typename T>
struct bar {};

template <typename funT, typename ...Args>
void foo(funT function_to_call, Args... args) {
  auto data = bar<typename std::result_of<funT(Args...)>::type>();
  (void) data;
  std::cout << typeid(typename std::result_of<funT(Args...)>::type).name() << std::endl;
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