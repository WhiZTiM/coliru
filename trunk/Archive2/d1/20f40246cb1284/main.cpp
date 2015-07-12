#include <iostream>
#include <type_traits>

struct A {
    double a, b, c, d;
};

int main(int argc, char** argv) {
    std::aligned_storage_t<sizeof(A), alignof(A)> storage[2];
    char* p = reinterpret_cast<char*>(storage);
    
    A* a = reinterpret_cast<A*>(p);
    A* b = reinterpret_cast<A*>(p + sizeof(A));
    
    new (a) A{1.0, 2.0, 3.0, 4.0};
    std::cout << a->a << " " << a->b << " " << a->c << " " << a->d << "\n";
    new (b) A(std::move(*a));
    std::cout << b->a << " " << b->b << " " << b->c << " " << b->d << "\n";
    return 0;
}