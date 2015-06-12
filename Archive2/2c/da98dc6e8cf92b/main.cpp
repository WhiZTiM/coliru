#include <iostream>
#include <string>
#include <vector>

struct A
{
  A(int, int) {}

  A(int p1 = 0, int p2 = 0, int p3 = 0) {}

  // There are a lot more of constructors for A class 
};

struct B : public A
{
 // using A::A; // I want to inherit many base constructors in order to save work

  // But I need this particular constructor and it should override the
  // equivalent base constructor
  B(int p1 = 0, int p2 = 0, int p3 = 0):A(0,0,0) {std::cout<<"created B";}
};

int main(int argc, char *argv[])
{
  B b(1); // gives "error: call to constructor of 'B' is ambiguous", what
      // of course is true, but I would want to inherit the other
      // base constructors
}

