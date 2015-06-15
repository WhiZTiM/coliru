#include <type_traits>
#include <iostream>

#define SHOW(S) std::cout << #S ": " << (S) << '\n'

#if __GNUC__ < 5 && ! defined __clang__
// http://stackoverflow.com/a/28967049/1353549
template <typename...>
struct voider
{
  using type = void;
};
template <typename...Ts>
using void_t = typename voider<Ts...>::type;
#else
template <typename...>
using void_t = void;
#endif

// See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4502.pdf.
// Primary template handles all types not supporting the operation.
template <class T, template <typename> class, typename = void_t<>>
struct detect : std::false_type {};

// Specialization recognizes/validates only types supporting the archetype.
template <class T, template <typename> class Op>
struct detect<T, Op, void_t<Op<T>>> : std::true_type {};

struct foo
{
  int bar()    { return 1; };
  int bar(int) { return 2; };

  using type = int;
};

struct baz
{
  int bar(int) { return 2; };
  void bar(const char*) {};
};

template <typename T>
using bar_t = decltype(std::declval<T>().bar());

template <typename T>
using bar_int_t = decltype(std::declval<T>().bar(0));

template <typename T>
using bar_string_t = decltype(std::declval<T>().bar("kdk"));

template <typename T>
using type_t = typename T::type;

int main()
{
  SHOW((detect<foo, bar_t>{}));
  SHOW((detect<foo, bar_int_t>{}));
  SHOW((detect<foo, bar_string_t>{}));
  SHOW((detect<foo, type_t>{}));
  
  SHOW((detect<baz, bar_t>{}));
  SHOW((detect<baz, bar_int_t>{}));
  SHOW((detect<baz, bar_string_t>{}));
  SHOW((detect<baz, type_t>{}));
}
