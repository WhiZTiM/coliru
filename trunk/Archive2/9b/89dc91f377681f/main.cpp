#include <iostream>

class Evil {
  int V;
    
public:
  Evil(int i) : V(i) {}

  // Oh great, now we have a vtable.
  virtual int haha() const { return V; }
    
  // Even better, we rely on the vtable...
  operator int() const { return haha(); }
};
  
struct StupidlyEvil : Evil {
  StupidlyEvil(int i) : Evil(i) {}
  int haha() const override { return Evil::haha() + 10; }
};

auto g() { // Deduced return type, since this relies on a type with a hidden name.
  // By using a class type that has a vtable, we ensure that the object cannot be located in
  // read-only memory that is statically initialized by the linker (and loader).
  static StupidlyEvil e(42);
  
  struct I { Evil &f() { return e; } };
  return I();
}

void f() {
  // Remember, decltype()'s operand is unevaluated, so g() is not actually executed.
  typedef decltype(g()) HiddenInnerType;
  HiddenInnerType HIT;

  // Want to make this stop crashing? Uncomment the next statement. It causes execution to
  // flow through the declaration of e.
  // g();
  
  std::cout << HIT.f(); // Call I::f() without ever executing g(), which in turn calls
                        // Evil::operator int(), which calls  the virtual method haha()...
}

int main() {
  f();
}