#include <iostream>

void f(const int n, const double a[]) {
  for (int i = 0; i < n; ++i) {
    std::cout << *a << "\n";
    a++;
  }
}

int main() {
  double a[] = {1., 2.};
  f(2, a);
}