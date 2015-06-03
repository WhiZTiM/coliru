#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

int main() {
  std::stringstream ss("1 0 1 0");
  std::vector<bool> vec(4);
  std::generate(std::begin(vec), std::end(vec), [&ss](){ int val; ss >> val; return val;});
  for(int i(0), sz(vec.size()); i < sz; ++i) std::cout << vec[i] << " ";
}