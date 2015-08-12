#include <iostream>
#include <array>

int main()
{
    std::array<std::array<int,3>,2> arrays = { { {1,2,3} , {4,5,6} } };
    
    // the std::arrays are contiguous, they are separated by sizeof(std::array<int,3>) bytes
    std::cout << &arrays[0] << " , " << &arrays[1] << '\n';
    std::cout << sizeof(std::array<int,3>) << '\n';
    
    // In this case, the elements of vectors[0] _are_ contiguous with respect to the elements of vectors[1] 
    std::cout << &arrays[0][2] << " , " << &arrays[1][0] << '\n';
    
    
    
}
