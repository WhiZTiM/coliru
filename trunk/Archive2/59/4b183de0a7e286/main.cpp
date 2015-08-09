#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    std::cout << "default format: " << 100 * std::sqrt(2.0) << '\n'
		<< "scientific " << std::scientific << 100 * std::sqrt(2.0) << '\n'
		<< "fixed_decimal " << std::fixed << 100 * std::sqrt(2.0) << '\n'
		<< "hexadecimal " << std::hexfloat << 100 * std::sqrt(2.0) << '\n'
		<< "use default: " << std::defaultfloat << 100 * std::sqrt(2.0) << std::endl;

	return 0;
}