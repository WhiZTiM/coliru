#include <iostream>

struct A {
    A(float ) { printf("a"); } // (a)
    A(int ) { printf("b");} // (b)
    A(double ) { printf("c"); } // (c)
};

int main() {
    A{1.1f}; // selects (a), (c) without (a)
    A{1.1}; // selects (c), ambiguity error without (c)
}
