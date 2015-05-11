#include <iostream>
#include <cstddef>

struct __attribute__((packed)) x {
    char a[3];
    char b[8];
    short c;
};

struct __attribute__((packed)) y {
    char a[3];
    char b[7];
    short c;
};


int main() {
	std::cout << sizeof( x ) << std::endl;
    std::cout << offsetof( x, a ) << std::endl;
    std::cout << offsetof( x, b ) << std::endl;
    std::cout << offsetof( x, c ) << std::endl;
}
