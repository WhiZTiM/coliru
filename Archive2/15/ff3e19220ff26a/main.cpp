#include <iostream>
#include <cmath>

int main () {
  float a = 3.563f, b, c = std::modf (a, &b);
  std::cout << a << " " << b << " " << c << std::endl;
}