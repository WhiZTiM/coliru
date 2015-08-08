#include <iostream>

int main()
{
    int foo[2] = {1, 2};
    std::cout << foo << '\n'; //prints address of an array
    std::cout << foo[0] << '\n'; //prints value of first element
}