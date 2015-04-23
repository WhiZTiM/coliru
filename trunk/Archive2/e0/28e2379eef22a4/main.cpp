#include <iostream>

template<typename T, int a>
void f() {
  if (a == 1) {
    std::cout << "Hello\n";
  } else {
    T("hello");
  }
}

int main() {
  f<int, 1>();
  return 0;
}