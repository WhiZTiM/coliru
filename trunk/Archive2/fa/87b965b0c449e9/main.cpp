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
  } catch (...) {
    auto fn = *(decltype(f()) *)&std::current_exception();
    fn();
  }
}

int main() {
  g();   
}