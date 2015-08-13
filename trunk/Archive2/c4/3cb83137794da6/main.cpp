#include <iostream>
#include <memory>

struct A {
  void print() { std::cout << "A" << std::endl; }
};

struct B : public A {
  void print() { std::cout << "B" << std::endl; }
};

int main() {
  std::shared_ptr<A> ptr_a(new A);
  std::shared_ptr<B> ptr_b(new B);
  
  ptr_a->print();
  ptr_b->print();
  
  ptr_a->B::print();
  ptr_b->A::print();
}
    