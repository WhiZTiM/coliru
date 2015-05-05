#include <iostream>
#include <utility>
#include <iterator>
#include <numeric>
#include <tuple>

    template<class...Ts>
    struct compare_with_t {
      using indexes=std::make_index_sequence<sizeof...(Ts)>;
      std::tuple<Ts...> values;
      template<size_t...Is, class F, class C>
      bool apply( std::index_sequence<Is...>, F&& f, C&& c, bool id) const {
        bool results[]={
          f( std::get<Is>(values) )...
        };
        return std::accumulate( std::begin(results), std::end(results), id, std::forward<C>(c) );
      }
      template<class O>
      bool operator!=( O&& o )const{
        return apply( indexes{}, [&o]( auto const&t ){ return o != t; }, [](bool a, bool b){return a&&b;}, true );
      }
      template<class O>
      bool operator==( O&& o )const{
        return apply( indexes{}, [&o]( auto&&t ){ return o == t; }, [](bool a, bool b){return a||b;}, false );
      }
      template<class O>
      friend bool operator==( O&& o, compare_with_t const& c ){
        return c==std::forward<O>(o);
      }
      template<class O>
      friend bool operator!=( O&& o, compare_with_t const& c ){
        return c!=std::forward<O>(o);
      }
    };
    template<class...Ts>
    compare_with_t<std::decay_t<Ts>...>
    compare_with( Ts&&...ts ) {
      return { std::forward_as_tuple( std::forward<Ts>(ts)... ) };
    }


int main() {
    std::cout << ( '%' != compare_with( '+', '-', '*', '/', '%' ) ) << '\n';
    std::cout << ( 'x' != compare_with( '+', '-', '*', '/', '%' ) ) << '\n';
    std::cout << ( '*' != compare_with( '+', '-', '*', '/', '%' ) ) << '\n';
    std::cout << ( '+' != compare_with( '+', '-', '*', '/', '%' ) ) << '\n';
    
    std::cout << ( '%' == compare_with( '+', '-', '*', '/', '%' ) ) << '\n';
    std::cout << ( 'x' == compare_with( '+', '-', '*', '/', '%' ) ) << '\n';
    std::cout << ( '*' == compare_with( '+', '-', '*', '/', '%' ) ) << '\n';
    std::cout << ( '+' == compare_with( '+', '-', '*', '/', '%' ) ) << '\n';
    
}