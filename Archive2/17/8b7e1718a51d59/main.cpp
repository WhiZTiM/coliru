#include <iostream>

struct S {
    int foo;
    
private:
    S();
};

int main() {
    std::cout << "Size of S::foo = " << sizeof(S{}.foo);
}