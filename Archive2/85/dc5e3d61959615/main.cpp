#include <iostream>
using namespace std;

struct Caller
{
   template <class T>
      auto operator()(const T &obj) -> decltype(&T::foo)
      {
         return &T::foo;
      }
};

struct X
{
   int foo() { return 3; }
};

int main()
{
   X x;
   auto meth_ptr = Caller{}(x);
   cout << (x.*meth_ptr)() << endl;
}