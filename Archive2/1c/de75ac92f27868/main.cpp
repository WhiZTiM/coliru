#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

std::vector<int> Convert(std::string const &s) {
  std::vector<int> res;
  for (auto i = s.data(), e = i + s.size(); i != e; i += 4)
    res.push_back(boost::lexical_cast<int>(i, 4));
  return res;
}

int main() {
  std::string s{"001200041234"};
  auto v = Convert(s);
  for (auto i : v) std::cout << i << "\n";
}