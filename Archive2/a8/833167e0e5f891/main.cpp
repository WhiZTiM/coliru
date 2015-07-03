#include <iostream>



int main()
{

    uint32_t numBytes = 0xFFFFFFFF -2;
    
    uint32_t test1 = numBytes & 0xffff | (1<<19);
    std::cout << "test1 is " << test1 << std::endl;
    
    uint32_t test2 = (numBytes & 0xffff) | (1<<19);
    std::cout << "test2 is " << test2 << std::endl;
    
    uint32_t test3 = numBytes & (0xffff | (1<<19));
    std::cout << "test3 is " << test3 << std::endl;
}
