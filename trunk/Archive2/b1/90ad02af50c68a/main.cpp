#include <iostream>

class A 
{ 
public:
  static void Function1(){std::cout << "1" << std::endl;}
  static void Function2(){std::cout << "2" << std::endl;}

public:
  static void(*functionPointer[2])();

};

void (*A::functionPointer[]) () =
{ A::Function1, A::Function2 };

int main()
{
    A a;
    a.functionPointer[0]();
    a.functionPointer[1]();
}