#include <initializer_list>
#include <iostream>

struct X {
    X(int, double) {}
    X(int, const char*) {}
    X(std::initializer_list<int>) { std::cout << "init\n"; }
};

int main() {
    // X x{1, 2.0}; // error: type 'double' cannot be narrowed to 'int' in initializer list [-Wc++11-narrowing]
    X x{1, "hello"}; // okay?
}