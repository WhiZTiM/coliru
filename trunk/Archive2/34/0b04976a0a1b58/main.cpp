#include <type_traits>

class Cls
{ enum { N }; };

template <typename T, typename U,
      typename std::enable_if_t<T::N == U::N>* = nullptr>
auto operator==(const T& a, const U& b)
{
  return T::N + U::N;
}

int main()
{
  Cls a, b;
  return a == b;
}
