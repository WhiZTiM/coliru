#include <iostream>

auto g() {
  class Evil {
    int V;
    
  public:
    Evil(int i) : V(i) {}
    operator int() const { return haha(); }
    
    virtual int haha() const { return V; }
  };
  
  struct StupidlyEvil : Evil {
    int haha() const override { return Evil::haha() + 10; }
  };
  
  static Evil e(42); // When does this initialization take place?
  struct I { Evil &f() { return e; } };
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