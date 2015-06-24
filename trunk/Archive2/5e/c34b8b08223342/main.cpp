#include <iostream>

struct X {
    X() { std::cout << "default ctor\n"; }
    X(const X&) { std::cout << "copy ctor\n"; }
    X& operator=(const X& ) { std::cout << "copy ass\n"; return *this; }
};

void by_ref(const X& ) { }
void by_ptr(const X* ) { }
void by_val(X ) { }

int main()
{
    X x;
    std::cout << "by ref\n";
    by_ref(x);
    std::cout << "by ptr\n";
    by_ptr(&x);
    std::cout << "by val\n";
    by_val(x);
}