#include <iostream>
#include <iomanip>

int main()
{
    const std::size_t digitsBehindComma = 1ULL;
    std::cout << std::setprecision(digitsBehindComma +1ULL) << 8.3333333f;
}
