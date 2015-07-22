#include <iostream>

extern int foo;

void f()
{
    std::cout << foo << '\n';
}

int main() {
    int foo = 7;
	f();
}