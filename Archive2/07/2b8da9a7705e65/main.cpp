#include <iostream>
#include <string>
 
 void dummy() {}
 
int main() 
{
    double f = 23.43;
    std::string f_str = std::to_string(f);
    std::cout << f_str << '\n';
    
    const char* blabla = reinterpret_cast<const char*>(&dummy);
    const char* something = "yeeah";
    
    try {
       std::cout << "hello " << std::string(blabla) << something << std::endl;
       std::cout << "goodbye" << std::endl;
    } catch(std::exception& e) {
        std::cout << "exception caught: " << e.what() << std::endl;
    }
}