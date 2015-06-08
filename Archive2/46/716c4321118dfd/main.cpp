#include <iostream>

int main()
{
    char a = 'a', b = 'b', c = 'c';
    std::operator<<(std::operator<<(std::operator<<(std::cout, a), b), c);
}