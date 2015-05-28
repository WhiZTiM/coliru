struct B {
  constexpr B () {}
};

struct A : B {
  using B::B;
};

template<bool B = noexcept (A{}), class X = A>
constexpr int func (X x = {}) {
  return B;
}

#include <iostream>

int main () {
  constexpr bool a = func ();
  constexpr bool b = func ();

  static_assert (a != b, "my upcoming gift to the reflector group");
  
  std::cout << a << " " << b << std::endl;
}
