#include <iostream>

void f(int a, int b) {
  std::cout << "a = " << a << ", b = " << b << std::endl;
  std::cout << "a / b = " << (a/b) << std::endl;
  std::cout << "(a / b) * b) = " << ((a/b)*b) << std::endl;
  std::cout << "a % b = " << (a % b) << std::endl;
  std::cout << "((a / b) * b) + (a % b) = " << (((a / b) * b) + (a % b)) << std::endl;
  std::cout << std::endl;
}

int main() {
  f(5, 3);
  f(-5, 3);
  f(5, -3);
  f(-5, -3);
}