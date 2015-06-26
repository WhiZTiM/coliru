#include <iostream>

class Foo {
  public: 
    Foo(const int& x) : x_(x) {
        std::cout << "a " << x << std::endl;    
    }
    void bar() {
        std::cout << "b " << x_ << std::endl;
    }
  private:
    const int& x_;
};

int main() {
    Foo f(2);
    f.bar();
}