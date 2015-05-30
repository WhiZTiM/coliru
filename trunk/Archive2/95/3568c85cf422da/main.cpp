#include <iostream>
struct A { int i; using Int = int; };

int main()
{
    std::cout << sizeof(A::Int) << '\n';
}
