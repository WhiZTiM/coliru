struct X {
  template<class, class = void>
  static const auto has_func = false;

  template<class T>
  static const auto has_func<T, decltype((void)&T::func)> = true;
};

int main () {
  struct A { void func (); };
  struct B { };

  static_assert (X::has_func<A> == 1, "!!");
  static_assert (X::has_func<B> == 0, "!!");
}