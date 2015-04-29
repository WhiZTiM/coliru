#include <iostream>
#include <iomanip>
#include <type_traits>

class Cls
{ public: enum { N=1 }; };

class Cls2
{ public: enum { X }; };

template <typename T, typename U>
auto operator==(const T& a, const U& b) -> decltype(T::N + U::N)
{
  return T::N + U::N;
}

int main()
{
  Cls a, b;
  Cls2 c;
  
  std::cout << std::boolalpha << (a == b /*|| a == c*/) << std::endl;
  return 0;
}
