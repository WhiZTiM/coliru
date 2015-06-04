#include <sstream>
#include <iostream>
#include <iomanip>

int main()
{
    std::string data = "89";
    std::stringstream ss;
    ss << std::setfill('1') << std::setw(5) << data;
    ss << " - ";
    ss << std::setfill('0') << std::setw(2) << 5;
    
    std::cout << ss.str();
}
