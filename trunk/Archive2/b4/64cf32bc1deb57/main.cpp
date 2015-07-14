#include <iostream>
int main()
{
    std::cout << (~(1LL << 63) & (1ULL << 63)) << ' ';
}