#include <iostream>
#include <limits>
int main()
{
    float a = std::numeric_limits<float>::infinity();
    float b = a + 1;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
}