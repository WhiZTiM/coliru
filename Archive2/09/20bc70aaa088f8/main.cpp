#include <iostream>
#include <string>
#include <vector>
#include <cmath>


int main()
{
    double angleA = 10, angleB = -20;
    std::cout << std::fmod(angleA + angleB, 360.0);
}
