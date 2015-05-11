#include <iostream>

struct x {
    char a[3];
    char b[8];
    short c;
};

struct y {
    char a[3];
    char b[7];
    short c;
};


int main() {
	std::cout << sizeof( x ) << std::endl;
	std::cout << sizeof( y ) << std::endl;
}
