#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v(2, 1);
    
    std::cout << &v << " " << &v[0] << std::endl;
    
    v.resize(500);
    
    std::cout << &v << " " << &v[0] << std::endl;
    
    return 0;
}