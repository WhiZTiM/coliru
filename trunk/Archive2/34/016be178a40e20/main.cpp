#include <iostream>
#include <type_traits>
#include <complex> 
class A {};
 
int main() 
{
    std::cout << std::boolalpha;
    std::cout << "A:           " <<  std::is_arithmetic<A>::value << '\n';
    std::cout << "int:         " <<  std::is_arithmetic<int>::value << '\n';
    std::cout << "int const:   " <<  std::is_arithmetic<int const>::value << '\n';
    std::cout << "int &:       " <<  std::is_arithmetic<int&>::value << '\n';
    std::cout << "int *:       " <<  std::is_arithmetic<int*>::value << '\n';
    std::cout << "float:       " <<  std::is_arithmetic<float>::value << '\n';
    std::cout << "float const: " <<  std::is_arithmetic<float const>::value << '\n';
    std::cout << "float &:     " <<  std::is_arithmetic<float&>::value << '\n';
    std::cout << "float *:     " <<  std::is_arithmetic<float*>::value << '\n';
    std::cout << "complex:     " <<  std::is_arithmetic<std::complex<float> >::value << '\n';
}