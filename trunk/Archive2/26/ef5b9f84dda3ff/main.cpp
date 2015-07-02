// skipws flag example
#include <iostream>     // std::cout, std::skipws, std::noskipws
#include <sstream>      // std::istringstream

int main () {
  size_t a, b, c, d, e, f, g;

  std::istringstream iss ("");
  size_t s[10000];
  for (int i = 0; i < 10000; i++) {
      std::cout << (char)s[i] << '\n';
  }
}