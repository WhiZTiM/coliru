#include <iostream>

struct S {
  bool b;
  
  S(bool b) : b(b) {
   std::cout << "Constructing" << std::endl;
  }
  
  S(const S &O) noexcept(false) {
    std::cout << "Copy construct" << std::endl;
    if (O.b) {
      throw S(false);
    }
  }
  
  S& operator=(const S &O) noexcept(false) {
    std::cout << "Copy assign" << std::endl;
    if (O.b) {
      throw S(false);
    }
    return *this;
  }
  
  // Should have no implicitly defined move constructor or assignment because there
  // are user-provided copy constructor and assignment operators.
  //
  // Copy constructor and copy assignment are not called in the absence of the
  // explicitly deleted move operators.
  //
  // When the move operators are explicitly deleted, they result in an ill-formed program.
  
//  S(S&&) = delete;
//  S& operator=(S&&) = delete;
};

void f() {
  try {
    std::cout << "Throwing" << std::endl;
    throw S(true); // ??? I would expect this to call the copy constructor, which throws, and then Bad Things
  } catch (S &s) {
    std::cout << "Caught" << std::endl;
  }
}

int main() {
  f();
}
