#include <initializer_list>
#include <iostream>

struct X {
    X(int, double) {}
    X(int, const char*) {}
    X(std::initializer_list<double>) { std::cout << "init\n"; }
};

int main() {
    X a{1, 2.0}; // nope
    X x{1, "hello"}; // okay?
}