#include <iostream>
#include <type_traits>
 
class A {};
 
int main() 
{

    std::cout << std::boolalpha;
    //Checking is_pointer
    std::cout << std::is_pointer<A>::value << '\n'; //false
    std::cout << std::is_pointer<A *>::value << '\n'; //true
    std::cout << std::is_pointer<A &>::value << '\n'; //false
    std::cout << std::is_pointer<int>::value << '\n'; //false
    std::cout << std::is_pointer<int *>::value << '\n'; //true
    std::cout << std::is_pointer<int **>::value << '\n';//true
    std::cout << std::is_pointer<int[10]>::value << '\n'; //false
    std::cout << std::is_pointer<std::nullptr_t>::value << '\n'; //false
    std::cout << std::is_pointer<int*&>::value << '\n'; //false
    std::cout <<std::is_pointer<int[][5]>::value << '\n'; //false
    std::cout << std::is_pointer<int***>::value <<'\n'; //true
    std::cout << std::is_pointer<int*[20]>::value <<'\n'; //false
    std::cout << std::is_pointer<int(*)[20]>::value << '\n'; //true
    
    //std::cout << std::is_pointer<int*[10]&>::value <<'\n';//compiler error
    //std::cout << std::is_pointer<int*&[]>::value << '\n'; //compiler error
    
    //Checking References
    std::cout << std::is_reference<int*&>::value <<'\n';  //true
}