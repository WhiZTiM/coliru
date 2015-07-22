#include <iostream>
#include <memory>

int main()
{
    int array[]{1, 2, 3, 4, 5};
    
    std::unique_ptr<int> pa{array[3]};
    
    std::cout << "array[3]: " << array[3] << std::endl;
    std::cout << "pa: " << *pa << std::endl;
}