#include <iostream>
#include <string>

int main()
{
    std::cout << (std::string("Hello ") + "World") << std::endl;
    std::cout << ("Hello " + std::string("World")) << std::endl;
    
    return 0;
}