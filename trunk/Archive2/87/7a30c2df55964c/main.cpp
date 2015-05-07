#include <iostream>
#include <cstdlib>
#include <string>

int main( )
{
    std::string a   ( "test" );
    std::string b   = "test";
    std::string c   { "test" };
    
    
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    
    return 0;
}