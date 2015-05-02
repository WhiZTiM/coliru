#include <iostream>
#include <string>


struct A {
    A() = default;
    A(const A&) = default;
     A& operator= (const A&) = delete;
};
int main()

{   
    A a1;
    A a2 = a1;
}