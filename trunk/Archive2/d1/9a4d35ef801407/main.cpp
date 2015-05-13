#include <iostream>

int main()
{
    int a = 4;
    int& b = a;
    
    std::cout << std::boolalpha << (&a == &b) << '\n';
}
