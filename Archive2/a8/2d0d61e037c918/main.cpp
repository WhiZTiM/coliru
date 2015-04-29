#include <iostream>
#include <iomanip>
#include <type_traits>

class Cls
{ public: enum { N=1 }; };

class Cls2
{ public: enum { X }; };

template <typename T, typename U,
          typename = typename std::enable_if_t<!std::is_enum<T>::value>,
          typename = typename std::enable_if_t<T::N==U::N>>
auto operator==(const T& a, const U& b)
{
  return true;
}

int main()
{
  Cls a, b;
  Cls2 c;
  
  std::cout << std::boolalpha << (a == b /*|| a == c*/) << std::endl;
  return 0;
}
