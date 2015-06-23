#include <iostream>

#define LOUD() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

void f(char) LOUD()

namespace A {
    struct B {
        friend void f(char);   // ::f(char) is a friend
        friend void f(int);    // A::f(int) is a friend
        
        void bf();
    };
    void B::bf()
    {
        f(1);  // calls A::f(int);
        f('x');  // also calls A::f(int) because ::f is hidden
    }
    void f(char) LOUD()
    void f(int) LOUD()
}

int main()
{
    A::B{}.bf();
}