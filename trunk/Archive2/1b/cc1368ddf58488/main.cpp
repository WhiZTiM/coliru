#include <iostream>
#include <type_traits>
#include <utility>
#include <array>
#include <cstddef>

// #define break_it
struct A {
    int operator*( char ) { return 3; }
    friend int operator*( A, std::nullptr_t ) { return 4; }
};
struct B {
    friend int operator*( B, const char* ) { return 5; }
    #ifdef break_it
    int operator*( std::size_t ) { return 6; }
    #endif
};

int operator*( A, int ){ return 1; }
int operator*( B, double ){ return 2; };

struct C:A,B{};

//you can dispatch:
int main() {
    C c;
    std::cout << c*1 << '\n';
    std::cout << c*2.0 << '\n';
    std::cout << c*'\3' << '\n';
    std::cout << c*nullptr << '\n';
    std::cout << c*"hello" << '\n';
    #ifdef break_it
    std::cout << c*sizeof(c) << '\n';
    #endif
}