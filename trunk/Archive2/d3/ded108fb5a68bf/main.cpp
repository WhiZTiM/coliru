enum s {};
enum u { z = -1u };

#include <iostream>

void foo( int ) { std::cout << "signed\n"; }
void foo( unsigned ) { std::cout << "unsigned\n"; }

int main() {
    foo( s() );
    foo( u() );
}
