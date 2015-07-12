#include <iostream>
struct X {
    X(){ std::cout << "2333" << std::endl; }
    X(int){ std::cout << "hhhh" << std::endl; }
};

void* operator new(std::size_t,X*)noexcept {
    return 0; 
}

X a;

int main() {
    new(&a) X(42);
}
