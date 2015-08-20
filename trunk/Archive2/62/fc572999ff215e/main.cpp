#include <iostream>
#include <string>
#include <sstream>

int main()
{
    std::istringstream iss("3.45, 6.23, 1.56");
    
    double a, b, c;
    char delim;
    iss >> a >> delim >> b >> delim >> c;
    std::cout << a << " " << b << " " << c;
    
    return 0;
}