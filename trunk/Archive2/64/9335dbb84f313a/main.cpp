#include <iostream>
#include <string>

int main()
{
    std::string a = "hi", b = " wor", c = "ld";
    std::operator<<(std::operator<<(std::operator<<(std::cout, a), b), c);
}