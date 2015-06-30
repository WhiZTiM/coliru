#include <iostream>

struct foo {
    static int counter;
    
    foo() {
        std::cout << "howdy\n";
        if(counter++ < 1) throw "foo";
        std::cout << "complete\n";
    }
};

int foo::counter = 0;

void f() {
    static foo x;
}

int main() {
    try {
        f();
    } catch(...) {
        f();
    }
}