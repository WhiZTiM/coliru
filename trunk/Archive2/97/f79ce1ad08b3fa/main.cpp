#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>


bool validateStep(const double& value, const double& base, const double& step)
{
    int div = std::abs(std::lround((value - base) / step));
    return std::abs(div * step - std::abs(value - base)) <= std::numeric_limits<double>::epsilon();
}

int main()
{
    double value, base, step;
    value = 30.0;
    base = 0.1;
    step = 0.1;
    std::cout << validateStep(value, base, step);
}
