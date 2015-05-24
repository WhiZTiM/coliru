#include <iostream>
#include <string>
#include <vector>

struct A {
    A (int, int){}
};

struct B {
    B (A,A){}
};
int main()
{
   B b({1,1},{1,1});
}
