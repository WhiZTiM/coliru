#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<unsigned> v1{ 1, 2, 3 }; 
    std::vector<unsigned> v2{ 1, 2, 3 }; 
    std::vector<unsigned> v3{ 3, 4 };
    
    std::cout << (v1 == v2) << std::endl;
    std::cout << (v1 < v3) << std::endl;
    std::cout << (v3 < v2) << std::endl;
    
    
    std::vector<std::vector<unsigned>> vv { v1, v2, v3 }; 
    
    auto it = std::find(vv.begin(), vv.end(), v3); 
    if (it != vv.end())
    {
        std::cout << "I found v3, it has the following elements\n"; 
        for (auto &&a : *it)
        {
            std::cout << a << std::endl;
        }
    }
    
}
