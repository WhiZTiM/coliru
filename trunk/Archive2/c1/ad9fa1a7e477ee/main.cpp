#include <iostream>


int main()
{
    for (int i = 1; i != 10000; ++i)
    {
        auto ptr = malloc(i);
        std::cout << int(i) << ' ' << ptr << ' '
            << (long(ptr) / 4096) << '/' << (long(ptr) % 4096)
            << '\n';
    }
}