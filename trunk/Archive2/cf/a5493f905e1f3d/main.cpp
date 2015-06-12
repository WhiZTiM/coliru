#include <iostream>

template<typename T>
struct Foo {
  T val = T();
};

template<typename T>
Foo<T>& operator<<(Foo<T> &out, T const &val) {
  out.val = val;
  return out;
}

int main() { 
  Foo<int> foo;
  foo << 10;
  std::cout << foo.val << std::endl;
}