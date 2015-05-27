#include <iostream>
#include <limits>

int main() {
    
    double x = std::numeric_limits<double>::quiet_NaN();
    
    bool b = (0 <= x || x <= 10);

    std::cout << std::boolalpha << b << std::endl;

	return 0;
}