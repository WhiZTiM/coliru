#include <algorithm>
#include <iterator>
#include <iostream>

int main()
{
    char array1[6] = "haha ";
    char array2[4] = "you";
    char array3[10];
    
    std::copy(std::begin(array1), std::end(array1), std::begin(array3));
    std::copy(std::begin(array2), std::end(array2), std::begin(array3)+5);
    
    for (auto el : array3)
        std::cout << el;
    std::cout << '\n';
}