#include <iostream>

void f(int i); // Declaration

void f(const int i) { // Redeclaration, definition
  std::cout << i << std::endl;
}

int main() {
  f(42);
}