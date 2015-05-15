#include <iostream>
 
// #define BAR
 
extern "C" {
  enum X {ONE};
  int foo();
#ifdef BAR
  X bar();
#endif
}

namespace a {
class A {
public:
  A(int a): a(a) {}
private:
  friend int ::foo();
#ifdef BAR
  friend X ::bar();
#endif
  int a;
};
}

extern "C" {
 int foo() {
  a::A a(1);
  std::cout << a.a << std::endl;
  return ONE;
}
#ifdef BAR
 X bar() {
  a::A a(2);
  std::cout << a.a << std::endl;
  return ONE;
}
#endif
}

int main()
{
  foo();
}