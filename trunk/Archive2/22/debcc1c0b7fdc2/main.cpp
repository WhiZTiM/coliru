#include <type_traits>

template<class, class = void> constexpr std::false_type has_func {};
template<class T>             constexpr std::true_type  has_func<T, decltype(&T::func, void())> {};

int main () {
  struct A { void func (); };
  struct B { };

  static_assert (has_func<A> == 1, "!!");
  static_assert (has_func<B> == 0, "!!");
}