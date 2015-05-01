#include <iostream>
#include <memory>
#include <utility>
#include <vector>

struct noisy {
    noisy(){std::cout << "ctor\n"; }
    ~noisy(){std::cout << "dtor\n"; }
    noisy(noisy const&){std::cout << "copy\n"; }
    noisy(noisy &&){std::cout << "move\n"; }
};

struct A {
    int m1;
    noisy m2;
    A( int ):m1( (noisy{}, void(), 0) ), m2() {
        noisy m3;
    }
};

int main() {
    A x = 3;
}