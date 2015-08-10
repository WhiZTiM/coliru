#include <iostream>
#include <cstdint>
#include <cmath>
#include <float.h>
#include <iomanip>

int main()
{
    float test = 1.1234567f;
    std::int32_t integerPart = static_cast<std::int32_t>(test);
    std::int32_t fractional = static_cast<std::int32_t>((test - integerPart) * std::pow(10, FLT_DIG + 1) + 0.5f);
    
    std::cout << "Integer part: " << integerPart << std::endl <<
                "Fractional: " << fractional << std::endl <<
                "Original: " << std::setprecision(FLT_DIG + 2) << test << std::endl;
    
    return 0;
}
