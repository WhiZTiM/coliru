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

Array arr{{2}};

constexpr int get()
{
    return ++arr[0];
}

int main() {
  std::cout << get() << get() << std::endl;
}
