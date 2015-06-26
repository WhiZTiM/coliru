#include <cmath>
#include <iomanip>
#include <iostream>
#include <cfloat>


 
int main()
{
   double value1 = 1.0, value2 = 1.01;
    
    std::cout << "Diff " << std::setprecision(20) << value2-value1 << std::endl; 
    
    std::cout << "The next representable double after " << std::setprecision(20) << value1
              << " is " << std::nextafter(value1, FLT_MAX) << std::endl; 
    
    value1 = 6048000.0, value2 = 6048000.01;
    
    std::cout << "Diff " << std::setprecision(20) << value2-value1 << std::endl; 
    
    std::cout << "The next representable double after " << std::setprecision(20) << value1
              << " is " << std::nextafter(value1, FLT_MAX) << std::endl; 
}