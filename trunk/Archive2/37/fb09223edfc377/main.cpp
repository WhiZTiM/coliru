#include <iostream>

namespace std {

template <class T>
struct A {
  T m_x{};
};

template <class T>
bool operator<(const A<T>& lhs, const A<T>& rhs) {
  cout << "std::operator<\n";
  return true;
}

template <typename T>
bool LessThan(const A<T>& lhs, const A<T>& rhs) {
  return lhs < rhs;
}

}

namespace buddy {

bool operator<(const std::A<double>& lhs, const std::A<double>& rhs) {
  std::cout << "buddy::operator<\n";
  return false;
};

}

using namespace buddy;

int main() {
  std::A<double> a1;
  std::A<double> a2;
  (void)(a1 < a2);
  std::LessThan(a1, a2);
  return 0;
}
