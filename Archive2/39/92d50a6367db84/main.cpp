#include <type_traits>
#include <iostream>
 
// foo1 overloads are enabled via the return type
void foo1(int = 0) 
{
    std::cout << "foo1: int\n";
}

int main()
{
    foo1(10); // OK, calls the second version of foo1()
}