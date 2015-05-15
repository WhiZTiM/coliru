#include <iostream>

auto g() {
  static int i = 42; // When does this initialization take place?
  struct I { int &f() { return i; } };
  return I();
}

void f() {
  // Remember, decltype()'s operand is unevaluated, so g() is never called.
  typedef decltype(g()) HiddenInnerType;
  HiddenInnerType HIT;
  std::cout << HIT.f(); // Call I::f() without ever executing g()
}

int main() {
  f();
}