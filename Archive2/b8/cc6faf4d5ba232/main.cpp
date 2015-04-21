#include <complex>

double f(double x) { return 1.; }

template <typename T>
std::complex<T> f(std::complex<T> x) { return std::complex<T>(); }

template <typename T>
class A {
  T _x;
public:
  A(const T& x) : _x(x) {}
  operator T() { return _x; }
};

int main() {
  A<double> da(1.);
  A<std::complex<double>> ca({1.,1.});
  f(da); // OK                                                                                                                  
  f(ca); // error                                                                                                               
  return 1;
}
