#include<iostream>

class Outer {
    struct TheFriend;
public:
    class Inner {
       friend struct TheFriend;
//    private:
       static const int i = -1;
    };
};
struct TheFriend{ void f() { std::cout << Outer::Inner::i << '\n'; } };


int main()
{
    TheFriend global;
    global.f();
}