#include <initializer_list>
#include <iostream>

int main() {
  auto x = {1,2,3,4,5};
  for (auto x:x) {
      std::cout << x;
  }
}