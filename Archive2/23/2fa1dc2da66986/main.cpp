#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
 
int main()
{
    std::vector<int> data = { 90,80,70,60,50,40,30,20,10};
    for (auto i : data)
        if (80 >= i )
        {
        std::cout << i << std::endl;
        break;
        }
 
    std::cout << * std::lower_bound(data.begin(), data.end(), 88);
}