#include <iostream>
#include <string>
#include <vector>

void f(char) { std::cout << "char\n"; }
void f(signed char) { std::cout << "signed char\n"; }
void f(unsigned char) { std::cout << "unsigned char\n"; }

int main()
{
    f('a');
    f(static_cast<signed char>('a'));
    f(static_cast<unsigned char>('a'));
}
