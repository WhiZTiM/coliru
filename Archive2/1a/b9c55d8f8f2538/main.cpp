#include <iostream>
#include <typeinfo>
#include <memory>


int main()
{
    int i = 1;
    i = i++;
    std::cout << i << "\n";
}