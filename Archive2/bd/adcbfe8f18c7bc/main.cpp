#include <iostream>
#include <type_traits>
#include <utility>
#include <array>

    template<size_t...>
    struct index_sequence {};
    namespace details {
      template<size_t Count, size_t...szs>
      struct sequence_maker : sequence_maker<Count-1, Count-1, szs...> {};
      template<size_t...szs>
      struct sequence_maker<0,szs...> {
        using type = index_sequence<szs...>;
      };
    }
    template<size_t Count>
    using make_index_sequence=typename details::sequence_maker<Count>::type;
    template<class...Ts>
    using index_sequence_for=make_index_sequence<sizeof...(Ts)>;

    template<class Sig>
    using result_of_t=typename std::result_of<Sig>::type;

    template<class Enum, Enum Count, template<Enum>class Z>
    struct magic_switch {
      template<class...Args>
      using R = result_of_t<Z<Enum(0)>(Args...)>;
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
      table( index_sequence<Is...> ) const {
        return {{
          f<Is, Args...>()...
        }};
      }
      template<class...Args>
      R<Args...> operator()(Enum n, Args&&...args) {
        static auto jump=table<Args...>(make_index_sequence<size_t(Count)>{});
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