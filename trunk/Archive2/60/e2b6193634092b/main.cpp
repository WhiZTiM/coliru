#include <complex>
#include <iostream>

template<typename T, typename Complex>
T& real(Complex& c)
{
  return reinterpret_cast<T[2]>(c)[0];
}

int main()
{
    std::complex<double> c(42., 1.);
    
    std::cout << real(c) << '\n';
}