#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>


long cantor(long x, long y)
{
    return (x + y) * (x + y + 1) / 2 + y; 
}


int main()
{
    for (int i = 0; i != 20; ++i)
    {
        for (int j = 0; j != 20; ++j)
        {
            std::cout << i << "x" << j << " => " << cantor(i, j) << '\n';
        }
    }
}

