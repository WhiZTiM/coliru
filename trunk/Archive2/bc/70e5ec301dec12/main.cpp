#include <type_traits>

int f(int i)
{
   return i;
}

template<class F, class T>
auto ExecFunc(F f, T arg) -> typename std::result_of<F(T)>::type
{
  return f(arg);
}

int main() {
   auto a = ExecFunc(f, 3);
   return 0;
}