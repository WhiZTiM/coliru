#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
 
    int min = 100;
    int avg = 250;
    int max = 5000;
    
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d(avg,max-avg);
 
    const int size = 1000;
    int hist[size];
    int total = 0;
    for(int n=0; n<size; ++n) {
        hist[n] = std::round(d(gen));
        int num = hist[n];
        if (hist[n] <= min) {
            hist[n] -= min;
            hist[n] *= -1;
            hist[n] += min;
        }
        std::cout << n << " = " << num << ", " << hist[n] << std::endl;
        total += hist[n];
    }
    std::cout << "total = " << total << ", avg = " << total/size << std::endl;
}