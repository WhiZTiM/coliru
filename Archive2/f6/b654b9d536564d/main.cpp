#include <iostream>

namespace detail {
  constexpr int flag (int);

  template<class Tag>
  struct writer {
    friend constexpr int flag (Tag) {
      return 1;
    }
  };
}

template<bool B, class Tag = int>
struct dependent_writer : detail::writer<Tag> { };

template<int(*pf)(int), int = pf(0)>
constexpr bool checker (int) {
  return true;
}

template<int(*pf)(int)>
constexpr bool checker (...) {
  return false;
}

int main () {
  constexpr int a = checker<detail::flag> (0);

  dependent_writer<false> {};

  constexpr int b = checker<detail::flag> (0);

  std::cout << a << " " << b << std::endl;
}