#include <iostream>
#include <string>

void foo(int& x)
{
    x = 1337;
}

int main()
{
   auto x = 42;
   
   //auto l = [&x] () -> decltype(auto) { return (x); }; // This works
   auto l = [&x] () { return (x); };                     // This doesn't
   
   foo(l());
   
   std::cout << x;
}
