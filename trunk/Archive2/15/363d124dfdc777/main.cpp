#include <complex>
#include <iostream>
 
int main()
{
   const double pi = acos(-1);
   const std::complex<double> i(0, 1);
 
   cout << fixed << " exp(i*pi) = " << std::exp(i * pi) << '\n';
}
