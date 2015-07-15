#include <cmath>
#include <iostream>
#include <string>
#include <vector>

auto k(double val)
{
    static const double p=1.0 / std::sqrt( 2.0 * M_PI);

    return p * std::exp(- 0.5 * (val*val));
}

auto kde(double x, std::vector<double> val, double h)
{
    int len=val.size();
    const double p = 1.0 / (h * len );

    double sum = 0;
    for(int i=0;i<len;i++)
        sum += k( (x - val[i]) / h );
    return p*sum;
 }


int main()
{
  const int n=100;
  std::vector<double> val(n);
  
  for(int i=0;i<n;i++)
    val[i] = (double)rand() / (1.0 + RAND_MAX);
    
  
  double x0=-10.0;
  double xN=10.0;
  int Nx=10000;
  double hx=(xN-x0)/(Nx-1);
  
  double integral=0.0;
  for(int i=0;i<Nx;++i)
  {
        double x=x0+i*hx;
        
        integral += hx * kde (x, val, 0.1);
  }
  
  std::cout<<"integral: "<<integral<<std::endl;
}
