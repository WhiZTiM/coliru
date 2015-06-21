#include <iostream>
#include <array>
#include <algorithm>
#include <functional>

int main() {
  std::array<int, 2> a = {1, 2};
  std::array<int, 2> b = {2, 1};
  std::array<int, 2> c;
  std::transform(a.begin(), a.end(), b.begin(), c.begin(), std::multiplies<int>());
  for(auto &&i : c) std::cout << i << " ";
  std::cout << std::endl;
}