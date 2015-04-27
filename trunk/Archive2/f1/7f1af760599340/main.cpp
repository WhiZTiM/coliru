#include <cstddef>
#include <array>
#include <iostream>
#include <type_traits>

namespace {
  
  template<size_t N>
  struct hierarchy : hierarchy<N+1> { static constexpr size_t value = N; };
  template<> struct hierarchy<10> { static constexpr size_t value = 10; };
  
  template<typename T> struct identity { using type = T; };
  template<typename T> using identity_t = typename identity<T>::type;
  
  template<size_t N> using size_v = std::integral_constant<size_t, N>;
  
  size_v<10> count(hierarchy<10> const &) { return {}; }
  
  template<typename T>
  struct wrapper {
    template<typename U = T>
    friend size_v<T::value> count(identity_t<U> const &) {
      return {};
    }
  };

  template<typename T> struct indirection : wrapper<T> {};

  template<
    typename T = hierarchy<0>,
    typename B = decltype(count(T{})),
    typename   = decltype(indirection<hierarchy<B() ? B() - 1 : 0>>{})
  >
  constexpr size_t f() {
    return B();
  }

}

constexpr std::array<size_t, 10> g() {
  return {f(), f(), f(), f(), f(),
          f(), f(), f(), f(), f()};
}

constexpr auto test = g();
static_assert( test[0] == 10, "" );
static_assert( test[1] ==  9, "" );
// ...
static_assert( test[9] ==  1, "" );

int main() {
  for(auto&& x : test) {
    std::cout << x << " ";
  }
  std::cout << std::endl;
  return 0;
}