#include <iostream>
#include <type_traits>
 
class A {};
 
int main() 
{
    std::cout << std::boolalpha;
    std::cout << std::is_fundamental<A>::value << '\n';
    std::cout << std::is_fundamental<int>::value << '\n';
    std::cout << std::is_fundamental<int&>::value << '\n';
    std::cout << std::is_fundamental<int*>::value << '\n';
    std::cout << std::is_fundamental<float>::value << '\n';
    std::cout << std::is_fundamental<float&>::value << '\n';
    std::cout << std::is_fundamental<float*>::value << '\n';
}