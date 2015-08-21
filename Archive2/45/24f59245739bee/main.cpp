#include <iostream>

struct B1 { virtual ~B1() {} };
struct B2 { virtual ~B2() {} };

struct Derived : B1, B2 {};

int main() {
  B2 *b = new Derived;

  std::cout << "B2 address: " << b << '\n';
  std::cout << "Derived address: " << dynamic_cast<Derived*>(b) << '\n';
  std::cout << "B1: " << static_cast<B1*>(dynamic_cast<Derived*>(b)) << '\n';

  delete b;
}
    
void *operator new(std::size_t size) {
  if (void *ptr = std::malloc(size)) {
    std::cout << "Allocated: " << ptr << '\n';
    return ptr;
  }
  throw std::bad_alloc();
}
    
void operator delete(void *ptr) noexcept {
  std::cout << "Deallocated: " << ptr << '\n';
  if (ptr) {
    std::free(ptr);
  }
}
