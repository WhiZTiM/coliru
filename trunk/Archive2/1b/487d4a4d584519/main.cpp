#include <iostream>

void fun()  
{
    class Test 
    {
    public:
       struct X
       {
          int v;
       } x;

       Test() {
          x.v = 10;
       }

       void method()
       {
          std::cout << "Local class called; v = " << x.v << std::endl;
       }
    };

    Test t;
    t.method();  
}

int main()
{
    fun();
}