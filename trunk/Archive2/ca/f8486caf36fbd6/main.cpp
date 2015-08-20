#include <memory>

// Declarations
class B;

class A {
  private:
    friend class B;
    std::unique_ptr<B> b_;
    
  public:
    A();
};

class B {
  public:
    B(A& a);
    
  private:
    A& a_;
};

// Definitions
A::A() : b_(new B(*this)) {}
B::B(A& a) : a_(a) {}



int main() {
    A a;
}