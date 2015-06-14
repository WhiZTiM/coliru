#include <iostream>
#include <type_traits>
#include <utility>
#include <array>

    template<class Enum, Enum Count, template<Enum>class Z>
    struct magic_switch {
      template<class...Args>
      using R = std::result_of_t<Z<Enum(0)>(Args...)>;
      template<class...Args>
      using F = R<Args...>(*)(Args&&...);
      
      template<size_t I, class...Args>
      F<Args...> f() const {
        using ret = R<Args...>;
        return +[](Args&&...args)->ret{
          using F=Z<Enum(I)>;
          return F{}(std::forward<Args>(args)...);
        };
      }
      template<class...Args, size_t...Is>
      std::array<R<Args...>(*)(Args&&...),size_t(Count)>
      table( std::index_sequence<Is...> ) const {
        return {{
          f<Is, Args...>()...
        }};
      }
      template<class...Args>
      R<Args...> operator()(Enum n, Args&&...args) {
        static auto jump=table<Args...>(std::make_index_sequence<size_t(Count)>{});
        return jump[size_t(n)](std::forward<Args>(args)...);
      }
    };
//then if you have an enum:

    enum class abc_enum { a, b, c, count };
//and a function object template:

    template<abc_enum e>
    struct stuff {
      void operator()() const {
        std::cout << (int)e << '\n';
      }
    };
//you can dispatch:
int main() {
    magic_switch<abc_enum, abc_enum::count, stuff>{}(abc_enum::b);
}