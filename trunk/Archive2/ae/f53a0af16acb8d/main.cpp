#include <array>
#include <typeinfo>
#include <utility>
#include <algorithm>
#include <iostream>

    template<class T, class...Ts>
    std::array<std::decay_t<T>, sizeof...(Ts)+1> make_array( T&& t, Ts&&...ts ) {
      return {{ std::forward<T>(t), std::forward<Ts>(ts)... }};
    }
    template<class F, class T, size_t N>
    std::array<T, N> sorted( std::array<T, N> arr ) {
      std::sort( begin(arr), end(arr), F{} );
      return arr;
    }
    struct p_type_info_sort {
      bool operator()( std::type_info const* lhs, std::type_info const* rhs ) const {
        return lhs->before(*rhs);
      }
    };

    template<class...Ts, class T>
    std::type_info const* which(T const& t) {
      static const auto table=sorted<p_type_info_sort>(make_array(
        (&typeid(Ts))...
      ));
      auto r = std::equal_range( begin(table), end(table), &typeid(t), p_type_info_sort{} );
      if (r.first==r.second) return nullptr;
      return *r.first;
    }
    
struct Base { virtual ~Base() {} };

struct A:Base {}; struct B:Base {};
struct C:Base {};

int main() {
    std::type_info const* pinfo = which<A, B>((Base const&)C{});
    std::cout << !!pinfo << '\n';
    if (pinfo)
        std::cout << (*pinfo ==typeid(A)) << '\n';

    pinfo = which<A, B>((Base const&)A{});
    std::cout << !!pinfo << '\n';
    if (pinfo)
        std::cout << (*pinfo ==typeid(A)) << '\n';
}