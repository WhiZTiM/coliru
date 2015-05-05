#include <iostream>

template<class T> T a = 0;
template<> auto a<int> = 1;

int main ()  {
  std::cout << a<double> << "\n";  // prints 0; OK
  std::cout << a<int> << "\n";  // prints 1
}