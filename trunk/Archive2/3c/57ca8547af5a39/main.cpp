#include <iostream>

std::string give_string_pls()
{
    return std::string("I'm a string");
}

int main()
{
    const std::string& good_string = give_string_pls();
    
    std::cout << good_string << std::endl;
}