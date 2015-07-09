#include <iostream>
#include <string>
#include <vector>

int main()
{
    try {
        double n = -5;
        double d = 0;
        double r = n / d;
        std::cout << n << "/" << d << "=" << r << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "exception " << e.what() << std::endl;
    }
}
