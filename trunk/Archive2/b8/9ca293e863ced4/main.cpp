#include <iostream>
#include <string>
#include <vector>

int main()
{
    unsigned short a = 65535;
    unsigned short b = 65535;
    unsigned short c = a+b;
    std::clog << a << " " << b << " " << c << "\n";
}
