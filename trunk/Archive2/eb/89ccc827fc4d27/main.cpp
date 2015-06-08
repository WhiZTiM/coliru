#include <type_traits>
#include <iostream>

template<typename T>
struct Foo;

template<>
struct Foo<int>{
  int ival = 10;
};

template<>
struct Foo<double>{
  double dval = 30.0;
};

int main() {
  Foo<int> f1;
  std::cout << f1.ival << std::endl;
  Foo<double> f2;
  std::cout << f2.dval << std::endl;
}