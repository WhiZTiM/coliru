#include <iostream>
#include <algorithm>
#include <utility>
#include <tuple>


int main()
{
    int a[] = {1,2,3,4,5};
    int b[5];
    std::tie(b[0], b[1], b[2], b[3], b[4]) = std::make_tuple(4, 3, 2, 1, 0);
    //std::copy_n(a, 5, b);
    for(int c : b)
        std::cout<< c << ' ';
}
