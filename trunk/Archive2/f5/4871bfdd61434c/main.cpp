#include <exception>
#include <iostream>

auto f() {
  auto fn = []() { std::cout << "Oh dear god"; };
  throw fn;
  return fn;
}

void g() {
  try {
    (void)f();
  } catch (decltype(f()) &fn) {
    fn();
  }
}

int main() {
  g();   
}