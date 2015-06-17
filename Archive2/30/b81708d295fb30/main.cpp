#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>

class S {
  int i;

public:
  S() : i(0) {}
  S(int i) : i(i) {}
  S(const S&) = default;
  S& operator=(const S&) = default;
  ~S() { std::cout << "S::~S()" << std::endl; }
  
  friend std::ostream& operator<<(std::ostream &os, const S &s) {
    os << "S: " << s.i;
    return os;
  }
};

void f() {
  std::unique_ptr<S> s = std::make_unique<S>(10);
}

int main() {
  f();
}
