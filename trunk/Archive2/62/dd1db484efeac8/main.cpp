#include <iostream>
#include <string>
#include <limits>

int main()
{
    double result = 3/2;
    std::clog << "result is: " << result << "\n";
    double result2 = static_cast<double>(3)/2;
    std::clog << "result2 is: " << result2 << "\n";
}
