#include <iostream>
#include <vector>
#include <array>

template<class T> using const_t=T const;

int main() {
  constexpr int b =  const_t<std::array<int, 1>>{{3}}[0];  // Doesn't work!
  int a[b]={1,2,3};
  for (auto x:a)
    std::cout << x;
  std::cout << '\n';
}