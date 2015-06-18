#include <iostream>
#include <string>
#include <vector>
#include <array>


int main()
{
    //int a[] = {1, 2, 3, 4}; // c - statically allocated array
    
    array<int, 5> a = {1, 2, 3, 4, 5}; // c++ statically array
    
    for (int item : a)
    {
        cout << item << endl;
    }

    return 0;
}
