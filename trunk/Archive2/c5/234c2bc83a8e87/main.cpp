#include <iostream>
#include <vector>
#include <cstdio>

namespace Ns
{

struct Foo;
std::ostream& operator<<(std::ostream& os, const Foo& x) { return os; }

struct Foo
{
   Foo(std::vector<int> i)
   {
      printf("HEHEE\n");
      std::cout << i;
   }
};

}

int main(int, char*[])
{
   Ns::Foo obj{{}};
   
   return 0;
}
