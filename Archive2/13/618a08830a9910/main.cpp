#include <iostream>

template<unsigned... args>
unsigned sum() { return (args + ...); }

int main()
{
    int val = sum<1, 2>();
    std::cout << val << '\n';
}  