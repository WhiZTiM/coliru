#include <string>
#include <iostream>
#include <iomanip>

int main()
{
    std::string line = "6.0";
    std::cout << std::setprecision(5) << std::fixed << atof(line.c_str()) << std::endl;
}