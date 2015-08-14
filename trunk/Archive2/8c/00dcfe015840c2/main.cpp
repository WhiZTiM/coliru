#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v(2, 1);
    
    std::cout << &v << " " << v.data() << std::endl;
    
    v.resize(50000);
    
    std::cout << &v << " " << v.data() << std::endl;
    
    return 0;
}