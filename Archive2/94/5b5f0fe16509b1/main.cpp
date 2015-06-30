#include <iostream>
#include <utility>

/// Define HAS_{NAME} to detect a member function.
#define HAS(Name)                                                       \
  template <typename T>                                                 \
  class has_ ## Name                                                    \
  {                                                                     \
  public:                                                               \
    /* Type made public to please Clang 3.7. */                         \
    template <typename C, typename... Args>                             \
      static auto Type(void*)                                           \
      -> decltype(std::declval<C>().Name(std::declval<Args>()...));     \
                                                                        \
    template <typename, typename...>                                    \
    static void Type(...);                                              \
                                                                        \
    template <typename... Args>                                         \
    using result_type = decltype(Type<T, Args...>(0));                  \
  }

/// Forward to function Name, if is exists.
#define FORWARD(Name)                                                   \
  template <typename... Args,                                           \
            typename Result                                             \
              = typename has_ ## Name<Base>::template result_type<Args...>>\
  auto Name(Args&&... args)                                             \
    -> Result                                                           \
  {                                                                     \
    return base.Name(std::forward<Args>(args)...);                      \
  }

#define DEFINE(Name)                            \
  HAS(Name);                                    \
  FORWARD(Name)


template <typename Base>
struct wrapper
{
  Base base;
  DEFINE(foo);
  DEFINE(bar);
};


#define PING()                                  \
  std::cerr << __PRETTY_FUNCTION__ << '\n'
struct foo_no_bar
{
  void foo(int)           const { PING(); }
  int foo(double)         const { PING(); return 1; }
  int foo(double, double) const { PING(); return 1; }
};

struct foo_and_bar
{
  void foo() const { PING(); }
  void bar()       { PING(); }
};

int main()
{
  wrapper<foo_and_bar> f;
  f.foo();
  f.bar();
  wrapper<foo_no_bar> b;
  b.foo(1);
  b.foo(1.0);
  b.foo(1.0, 2.0);
}