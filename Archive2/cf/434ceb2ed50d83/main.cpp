#include <iostream>

int main()
{
    int a = 2, b = 3, c = 4;
    std::cout.operator<<(a).operator<<(b).operator<<(c);
}