#include <iostream>
#include <functional>
#include <algorithm>

int main()
{
    const int size = 9;
    int x[9] = {1,2,3,4,5,6,7,8,9};
    
    auto pos = std::upper_bound(x, x + size, 5) - x;

    std::cout << "position: " << pos;

    return 0;
}