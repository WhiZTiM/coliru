#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

int main() {
  std::stringstream ss("1 0 1 0");
  std::vector<bool> vec;
  std::copy(std::istream_iterator<bool>(ss), {}, std::back_inserter(vec));
  for(int i(0), sz(vec.size()); i < sz; ++i) std::cout << vec[i] << " ";
}