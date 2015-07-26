#include <iostream>
#include <algorithm>
#include <cctype>
 
int main()
{
  std::vector<char> v1 {'a', 'b', 'c', 'f', 'h', 'x'};
  std::vector<char> v2 {'a', 'b', 'c'};
  std::vector<char> v3 {'a', 'c'};
  std::vector<char> v4 {'g'};
  std::vector<char> v5 {'a', 'c', 'g'};
  std::vector<char> v6;
 
  for (auto i : v1) std::cout << i << ' ';
  std::cout << "includes:\n";
 
  for (auto i : v2) std::cout << i << ' ';
  std::cout << ": " << std::includes(v1.begin(), v1.end(), v2.begin(), v2.end()) << '\n';
  for (auto i : v3) std::cout << i << ' ';
  std::cout << ": " << std::includes(v1.begin(), v1.end(), v3.begin(), v3.end()) << '\n';
  for (auto i : v4) std::cout << i << ' ';
  std::cout << ": " << std::includes(v1.begin(), v1.end(), v4.begin(), v4.end()) << '\n';
  for (auto i : v5) std::cout << i << ' ';
  std::cout << ": " << std::includes(v1.begin(), v1.end(), v5.begin(), v5.end()) << '\n';
  for (auto i : v6) std::cout << i << ' ';
  std::cout << ": " << std::includes(v1.begin(), v1.end(), v6.begin(), v6.end()) << '\n';
 
  auto cmp_nocase = [](char a, char b) {
    return std::tolower(a) < std::tolower(b);
  }
  std::vector<char> v7 {'A', 'B', 'C'};
  for (auto i : v7) std::cout << i << ' ';
  std::cout << ": "
            << std::includes(v1.begin(), v1.end(), v7.begin(), v7.end(), cmp_nocase)
            << '\n';
}