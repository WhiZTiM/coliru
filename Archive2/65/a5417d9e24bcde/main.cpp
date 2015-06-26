#include <iostream>
#include <type_traits>

struct foo
{
  template<bool P>
  static std::enable_if_t<P> bar()
  {
    std::cerr << "P is true\n";
  }

  template<bool P>
  std::enable_if_t<!P> bar()
  {
    std::cerr << "P is false\n";
  }
};

int main()
{
  foo f;
  f.bar<false>();
}