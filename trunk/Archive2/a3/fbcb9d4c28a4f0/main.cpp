#include <type_traits>

template <int N> class Num { };

class Zero { };

template <int N, int M>
Num<N + M> operator+(Num<N>, Num<M>)
{
  return {};
}

template <int N>
Zero operator+(Num<N>, Num<-N>)
{
  return {};
}

int main()
{
  Num<1> one;
  Num<-1> mone;
  Num<0> null;

  auto a = one + one;
  static_assert(std::is_same<decltype(a), Num<2>>::value, ":(");

  auto b = one + mone;
  static_assert(std::is_same<decltype(b), Zero>::value, ":(");

  auto c = null + null;
  static_assert(std::is_same<decltype(c), Zero>::value, ":(");
}