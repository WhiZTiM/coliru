#include <iostream>
#include <string>
#include <vector>

struct A {
  int a;  
};

struct B {
  int a;  
};

struct AB: public A, public B{
  void print() {
    std::cout << A::a << std::endl;   
  }
};

int main()
{
    AB ab;
    ab.A::a = 1;
    ab.print();
    std::cout << ab.B::a << std::endl;
    return 0;
}
