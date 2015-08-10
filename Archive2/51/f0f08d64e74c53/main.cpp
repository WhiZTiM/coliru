#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>

float fd(float x, float y)
{
    float distance;
    x = pow(x, 2.0f);
    y = pow(y, 2.0f);
    distance = x + y;
    distance = sqrt(distance);
    return distance;
}

int main()
{
    std::vector<float> dv {19.5, 380, 361.5, 681.5, 889.5, 360.5, 342, 662, 870, 18.5, 301.5};

    std::vector<float> dr {4.6, 7.02, 8.18, 8.96, 9.65, 2.38, 3.54, 4.32, 5.022, 1.16, 1.94};
    
    std::vector<float> output;
    
    std::transform(begin(dv), end(dv), begin(dr), std::back_inserter(output), &fd);
    
    for (auto f : output)
        std::cout << f << " ";
}
