#include <math.h>
#include <iostream>
#include <limits>

float nearest_x_dot_5(float x)
{
    return round(x - 0.5) + 0.5;
}

int main() {
    float v[] = { -3.64 , -3.12, -2.90, -0.45, 0.01, 7.65, 8.45, 9.63, std::numeric_limits<float>::epsilon(), std::numeric_limits<double>::epsilon() };
    for (auto i : v) {
        std::cout << nearest_x_dot_5(i) << std::endl;
    }
}
