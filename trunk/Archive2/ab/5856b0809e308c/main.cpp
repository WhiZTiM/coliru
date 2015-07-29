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
  // Initialize constexpr from a non-const Array && temporary's operator[].
  constexpr int d = Array{{2}}[0];
  (void) d;  // Suppress unused warning.

  Array array{{2}};
  std::cout << "array[0]: " << array[0] << std::endl;
  // Check that the non-const array's operator[] is still non-const despite being constexpr.
  std::cout << "++array[0]: " << ++array[0] << std::endl;
  return 0;
}
