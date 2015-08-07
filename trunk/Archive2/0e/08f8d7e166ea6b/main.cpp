#include<iostream>
#include <algorithm>

int main()
{
    const int size = 6;
    int array[size ] = {1, 4, 6, 3, 2, 5};
    std::sort(array, array + size);
    for(int i: array) 
        std::cout << i << ' ';
}