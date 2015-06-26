#include<iostream>

struct Outer {
    struct TheFriend{ void f() {std::cout << Inner::i << '\n'; } };
    struct Inner {
       friend struct TheFriend;
       static const int i = -1;
    };
};
struct TheFriend{ void f() { std::cout << Outer::Inner::i << '\n'; } };


int main()
{
    TheFriend global;
    Outer::TheFriend outer;
    global.f();
    outer.f();
}