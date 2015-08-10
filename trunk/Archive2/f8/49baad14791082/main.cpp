#include <iostream>
#include <memory>

template <typename Ty>
struct special_unique_ptr : std::unique_ptr<Ty> {
  special_unique_ptr(Ty *P) : std::unique_ptr<Ty>(P) {}
  special_unique_ptr(special_unique_ptr<Ty> &&Other) : std::unique_ptr<Ty>(std::move(Other)) { std::cout << "move ctor called" << std::endl; }
};

void g(special_unique_ptr<int> ptr) {
  std::cout << *ptr << std::endl;    
}

void f() {
  special_unique_ptr<int> ptr(new int);
  *ptr = 42;
  g(std::move(ptr));
}

int main() {
  f();
}
