#include <iostream>
#include <algorithm>
#include <string>

int main() {
  std::string str("123456789");
  int s(0);
  std::accumulate(str.begin(), str.end(), 0, [&s](char const a, char const b) { s += (b - '0'); return 0; });
  std::cout << s << std::endl;
}