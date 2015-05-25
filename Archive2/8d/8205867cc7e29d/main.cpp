#include <iostream>

int main()
{
    int i = 1; 
    i = (i = i + 1) + 1;
    int j = 1;
    j = j++ + 1;
    std::cout << i << std::endl;
    std::cout << j << std::endl;
}