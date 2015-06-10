#include <iostream>

unsigned long getPow10(unsigned int n)
{
    static unsigned long pow10Table[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    if ( n < sizeof(pow10Table) / sizeof(pow10Table[0]))
       return pow10Table[n];
    return 0;
}

int main()
{
    std::cout << getPow10(4);
}