#include <cmath>

enum class Foo : int {
    value = static_cast<int>(std::pow(3.3, 3.3))
};

#include <iostream>
int main() {
  std::cout << static_cast<int>(Foo::value) << std::endl;
}