#include <iostream>
class A
{
    
public:
   A(){}
   int foo(int a)
   {
      return a;
   }
};

class B
{

private:
   int (A::*pFoo)(int);

public:
  
  B(int (A::*_pFoo)(int))
  {
     pFoo = _pFoo;
  }
  
  int cFoo(int i)
  {
     A* a;
   return (a->*pFoo)(i); //this causes a problem
  }

};

int main(){
A a;
B b(&A::foo);

std::cout<<b.cFoo(4);
}