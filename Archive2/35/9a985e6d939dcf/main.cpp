#include <iostream>

struct A {
  virtual ~A() {}
};

struct B {
  virtual ~B() {};
  
  void foo() {
    A* pA = dynamic_cast<A*>(this);
    std::cout << (pA ? "yay!\n" : "nay!\n"); 
  }
};

struct X : A, B
{};

int main()
{
  X x;
  x.foo();
}