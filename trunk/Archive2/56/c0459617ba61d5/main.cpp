#include <iostream>
#include <functional>
#include <typeinfo>

int add(int a, int b) {return a + b;}

int main() {
    
    //I believe this here is just a special type of bound function.
    auto add2 = std::bind(add, std::placeholders::_1, 2);
    
    //Yup.
    std::cout << typeid(add2).name() << std::endl;
    //Here's the type of the first function.
    std::cout << typeid(add).name() << std::endl;
    //The new function.
    std::cout << add2(1) <<  std::endl;
    
    return 0;   
}