#include <iostream>     // std::cout
#include <functional>   // std::plus
#include <vector>       // std::vector
#include <algorithm>    // std::transform

int main () {
  std::vector<double> a {1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> b {5.0, 4.0, 3.0, 2.0, 1.0};
  std::vector<double> res(a.size());
  
  std::transform(std::begin(a), std::end(a), std::begin(b), std::begin(res), std::plus<double>());

  for(auto i : res) std::cout << i << " ";
  std::cout << std::endl;

  return 0;
}