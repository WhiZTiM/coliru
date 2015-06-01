#include <iostream>
#include <string>
 
int main() 
{
    double f = 23.43;
    std::string f_str = std::to_string(f);
    std::cout << f_str << '\n';
    
    const char* blabla = nullptr;
    const char* something = "yeeah";
    std::cout << "hello " << blabla << something << std::endl;
    std::cout << "goodbye" << std::endl;
}