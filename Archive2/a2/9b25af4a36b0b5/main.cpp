#include <iomanip>
#include <iostream>

int main()
{
    double d = 1.23456789;
	std::cout << d << '\n';
	std::cout << std::fixed << std::setprecision(3) << d << '\n';
}