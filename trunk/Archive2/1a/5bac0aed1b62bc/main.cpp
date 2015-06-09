#include <iostream>

void f(const int n, const double * const a) {
  for (int i = 0; i < n; ++i) {
    std::cout << *a << "\n";
    a++; // This should not compile
  }
}

int main() {
  double a[] = {1., 2.};
  f(2, a);
}