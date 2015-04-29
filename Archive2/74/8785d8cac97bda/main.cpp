template<class, class = int> const auto has_func = false;
template<class T>            const auto has_func<T, decltype(&T::func, 0)> = true;

int main () {
  struct A { void func (); };
  struct B { };

  static_assert (has_func<A> == 1, "!!");
  static_assert (has_func<B> == 0, "!!");
}