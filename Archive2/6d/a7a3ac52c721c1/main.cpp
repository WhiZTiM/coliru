#include <algorithm> // std::max
#include <iostream>
#include <limits>

template <class T>
T max(const T& p1,
      const T& p2 = std::numeric_limits<T>::min(),
      const T& p3 = std::numeric_limits<T>::min(),
      const T& p4 = std::numeric_limits<T>::min(),
      const T& p5 = std::numeric_limits<T>::min(),
      const T& p6 = std::numeric_limits<T>::min(),
      const T& p7 = std::numeric_limits<T>::min(),
      const T& p8 = std::numeric_limits<T>::min(),
      const T& p9 = std::numeric_limits<T>::min(),
      const T& p10 = std::numeric_limits<T>::min()) {
  return std::max(p1, std::max(p2, std::max(p3, std::max(p4,
                  std::max(p5, std::max(p6, std::max(p7,
                  std::max(p8, std::max(p9, p10)))))))));
}

int main() {
    std::cout << max(1, 2) << "\n";
    std::cout << max(1, 3, 2, 4, 6, 5, 9, 7);
    return 0;
}
