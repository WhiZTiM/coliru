#include <iostream>
#include <fstream>
#include <iterator>

int main ()
{
    system ("echo \"hello\" > foo");
    std::ifstream f ("foo");
    char i1;
    char i2;
    f >> i1;
    f >> i2;
    while (f.good())
    {
        std::cout << i1 << ' ' << i2 << std::endl;
        f >> i1;
    }
}