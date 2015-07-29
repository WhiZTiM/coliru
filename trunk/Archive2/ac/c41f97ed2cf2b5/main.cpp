#include <iostream>
#include <fstream>
#include <iterator>

int main ()
{
    system ("echo \"hello\" > foo");
    std::ifstream f ("foo");
    std::istream_iterator<char> i1 (f);
    std::istream_iterator<char> i2 (f);
    while (i1 != std::istream_iterator<char> ())
    {
        std::cout << *i1 << ' ' << *i2 << std::endl;
        ++i1;
    }
}