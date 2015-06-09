#include <algorithm>
#include <iostream>
 
const int n = 42;

inline int f(int k) {
  return std::max(k, n);
}

int main() {
  std::cout << f(100) << ", " << f(12) << std::endl;
}