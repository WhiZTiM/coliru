#include <iostream>
#include <type_traits>
#include <utility>
#include <array>

struct A {};
struct B {};

int operator*( int, A ){ return 1; }
int operator*( double, B ){ return 2; };

struct C:A,B{};

//you can dispatch:
int main() {
    C c;
    std::cout << 1.0*c << '\n';
}