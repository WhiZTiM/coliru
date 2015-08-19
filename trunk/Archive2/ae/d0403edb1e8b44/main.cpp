#include <iostream>
#include <string>

std::string s = "Blah";

int main()
{
    std::string s = "World";
    ::s = "Hello ";
    
    std::cout << ::s << s << std::endl;
    
    return 0;
}