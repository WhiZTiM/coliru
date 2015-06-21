#include <cstdlib>
#include <iostream>

int main ()
{
    char *p;
    long double l = strtold("12312.12345", &p);
    std::cout << l << std::endl;
}
