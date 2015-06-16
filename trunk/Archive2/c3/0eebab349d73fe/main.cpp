#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>

    template<class R>
    R sort_the_range( R&& r ) {
      using std::begin; using std::end;
      std::sort( begin(r), end(r) );
      return std::forward<R>(r);
    }

    template<class T> struct tag{using type=T; };
    template<class...>struct types{using type=types;};
    template<class Tag>using type_t=typename Tag::type;

    template<class Default, class...Ts,
      class=typename std::enable_if<!std::is_same<void,Default>::value>::type
    >
    constexpr tag<Default> type_from( tag<Default>, Ts... ) { return {}; }
    template<class T0, class...Ts>
    constexpr tag<T0> type_from( tag<void>, tag<T0>, Ts... ) { return {}; }

    template<class Default, class...Ts>
    using type_from_t = type_t< decltype( type_from( tag<Default>{}, tag<Ts>{}... ) ) >;

    // explicit T argument is optional:
    template<class ExplicitType=void, class...Ts,
      // deduce return type:
      class R=type_from_t<ExplicitType, typename std::decay<Ts>::type...>
    >
    std::vector<R> make_vector( Ts&&... ts ) {
      using test = decltype(std::tuple<type_from_t<R,Ts>...>( std::declval<Ts>()... ));
      (void)test{};
      std::vector<R> retval;
      retval.reserve( sizeof...(ts) );
      (void)std::initializer_list<int>{0,((
        retval.emplace_back(std::forward<Ts>(ts))
      ),void(),0)...};
      return retval;
    }

    template<class T=void, class...Ts>
    auto make_sorted_vector(Ts&&...ts)
    ->decltype( make_vector<T>(std::forward<Ts>(ts)...) )
    {
      return sort_the_range(
        make_vector<T>( std::forward<Ts>(ts)... )
      );
    }

struct evil {
    template<class T>
    explicit operator T(){return {};}
};
struct good {
    template<class T>
    operator T(){return {};}
};
struct testing {
    template<class T>
    explicit testing(T&&){}
};
int main() {
    auto foo = make_sorted_vector(1,2,3);
    auto foo2 = make_sorted_vector<int>('a','c','b', good{});
    for(auto x:foo) std::cout << x << ',';
    std::cout << '\n';
    for(auto x:foo2) std::cout << x << ',';
    std::cout << '\n';
}