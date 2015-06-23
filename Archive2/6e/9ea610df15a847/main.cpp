#include <iostream>

// Assume f and g have not yet been declared.
void h(int);
template <class T> void f2(T);
namespace A {
    class X {
    public:
        friend void f(X); // A::f(X) is a friend
        class Y {
            friend void g(); // A::g is a friend
            friend void h(int); // A::h is a friend
            // ::h not considered
            friend void f2<>(int); // ::f2<>(int) is a friend
            int x = 42;
        };
    };
    // A::f, A::g and A::h are not visible here
    X x;
    void g() { f(x); } // definition of A::g
    void f(X) { /* ... */} // definition of A::f
    void h(int) { /* ... */ } // definition of A::h
    // A::f, A::g and A::h are visible here and known to be friends
}
using A::x;
void h() {
    A::f(x);
    //A::X::f(x); // error: f is not a member of A::X
    //A::X::Y::g(); // error: g is not a member of A::X::Y
}

template <class T> void f2(T) {
    A::X::Y y;
    std::cout << y.x << std::endl;
}

int main() {
    f2(0);
    // f2('a'); would generate error
}