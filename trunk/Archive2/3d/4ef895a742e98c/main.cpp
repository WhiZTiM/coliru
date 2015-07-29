#include <iostream>

struct Array {
  int elements_[1];
  
  constexpr const int &operator[](size_t n) const {
    return elements_[n];
  }
  
  constexpr int &operator[](size_t n) {
    return elements_[n];
  }
};

int main() {
  constexpr int d = Array{{2}}[0];
  (void) d;
  
  Array array{{2}};
  std::cout << "array[0]: " << array[0] << std::endl;
  std::cout << "++array[0]: " << ++array[0] << std::endl;
  return 0;
}