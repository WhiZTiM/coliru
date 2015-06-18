#include <iostream>
#include <functional>
#include <typeinfo>
#include <vector>

int add(int a, int b) {return a + b;}

int main() {
    
    //I believe this here is just a special type of bound function.
    auto add2 = std::bind(add, std::placeholders::_1, 2);
    auto add3 = std::bind(add, std::placeholders::_1, 3);
    
    //Yup.
    std::cout << typeid(add2).name() << std::endl;
    //Here's the type of the second function
    std::cout << typeid(add3).name() << std::endl;
    
    //Is there a nicer way to do this?
    std::vector<decltype(std::bind(add, std::placeholders::_1, 1))> vec;
    
    return 0;   
}