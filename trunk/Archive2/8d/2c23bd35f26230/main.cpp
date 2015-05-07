#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<unsigned char> vec;
    
    int myInt = 5;
    
    std::copy ((void*) &myInt, (void*) (&myInt + 1), std::back_inserter (vec));
    
    for (size_t u = 0; u < vec.size (); ++u)
    {
        std::cout << vec[u] << " ";
    }
    return 0;
}