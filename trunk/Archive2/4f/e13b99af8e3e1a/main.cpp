#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
 
int main()
{
    std::vector<double> y{0.0004, 0.0003, 0.0002, 0.0001, -0.0001, -0.0002, -0.0003, -0.0004};
    std::vector<double> x{0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.08};
 
    //int sum = std::accumulate(y.begin(), y.end(), 0);
    int n = x.size();
    double avgX = std::accumulate(x.begin(), x.end(), 0.0) / n;
    double avgY = std::accumulate(y.begin(), y.end(), 0.0) / n;
    
    double numerator = 0.0;
    double denominator = 0.0;

    for(int i=0; i<n; ++i){
        numerator += (x[i] - avgX) * (y[i] - avgY);
        denominator += (x[i] - avgX) * (x[i] - avgX);
    }

   double Der=numerator/denominator;

 
    std::cout << "avgY: " << avgY << '\n'
              << "avgX: " << avgX << '\n'
              << "Numerator: " << numerator << '\n'
              << "Denominator: " << denominator << '\n'
              << "2Der: " << Der << '\n';
}