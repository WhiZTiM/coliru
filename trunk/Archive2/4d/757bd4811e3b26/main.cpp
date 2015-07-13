#include <iostream>

char x[1];
struct Outer {
    struct Inner {
        char a[sizeof(x)];
        void f() { std::cout << sizeof(x) << "\n"; }
    };
    char x[2];
    char c[sizeof(x)];
};

int main()
{
    Outer::Inner().f();
}