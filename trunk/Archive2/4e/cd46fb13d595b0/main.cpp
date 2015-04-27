#include <iostream>
#include <algorithm>



int main()
{
    int a[] = {1,2,3,4,5};
    int b[5];
    std::copy_n(a, 5, b);
    for(int c : b)
        std::cout<< c << ' ';
}
