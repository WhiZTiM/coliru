#include <iostream>
#include <string>
#include <typeinfo>

class ClassA
{
  public:
      ClassA();
      int a;
      void doSomethingA();
};

class ClassB
{
  public:
      ClassB(A * A_instance_ptr)
      {
        A_ptr = A_instance_ptr;
      }
      void doSomethingB()
      {
         b = A_ptr->a;
      }
  private: 
      A *A_ptr;
      int b;
};

int main(int argc, char **argv)
{

  A A_instance;
  A_instance.a = 10;
  A_instance.doSomething();

  A* A_ptr;
  A_ptr = &A_instance;
  B B_instance(A_ptr); // commenting this line, the code compiles fine

  return 0;
}