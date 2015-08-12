#include <iostream>
#include <vector>

int main()
{
    std::vector<std::vector<int>> vectors = { {1,2,3} , {4,5,6} };
    
    // the std::vectors are contiguous, they are separated by sizeof(std::vector<int>) bytes
    std::cout << &vectors[0] << " , " << &vectors[1] << '\n';
    std::cout << sizeof(std::vector<int>) << '\n';
    
    // However, the elements of vectors[0] are _not_ contiguous with respect to the elements of vectors[1] 
    std::cout << &vectors[0][2] << " , " << &vectors[1][0] << '\n';
    
    
}
