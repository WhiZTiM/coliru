#include <sstream>
#include <iostream>
#include <string>
#include <utility>

    struct Thing {
      int a, b;
      friend void load (std::istream& is, Thing& t) {is >> std::skipws >> t.a >> t.b;}
    };

    struct Object {
      int a, b, c;
      void load (std::istream& is) {is >> std::skipws >> a >> b >> c;}
    };

    namespace meta {
      namespace details {
        template<template<class...>class Z, class always_void, class...Ts>
        struct can_apply : std::false_type {};
        template<template<class...>class Z, class...Ts>
        struct can_apply<Z, decltype(void(std::declval<Z<Ts...>>())), Ts...>:
          std::true_type
        {};
      }
      template<template<class...>class Z, class...Ts>
      using can_apply = details::can_apply<Z,void,Ts...>;
    }
    template<class T>
    using member_load = decltype( std::declval<T>().load(std::declval<std::istream&>()) );

    template<class T>
    using stream_load = decltype( std::declval<std::istream&>() >> std::declval<T>() );

    template<class T>
    using has_member_load = meta::can_apply< member_load, T >;
    template<class T>
    using has_stream_load = meta::can_apply< stream_load, T >;

    namespace loading {
      void load(std::istream&is, std::string& s) {
        while (std::getline (is, s) && s.empty());
      }
      template<class T>
      std::enable_if_t<has_member_load<T&>::value>
      load(std::istream&is, T& t) {
        t.load(is);
      }
      // uses ... to keep lowest priority:
      template<class T>
      std::enable_if_t<has_stream_load<T&>::value>
      load(std::istream& is, T& t, ...) {
        is >> t;
      }

      template<class...Ts>
      void load_many(std::istream&is, Ts&...ts) {
        using discard=int[];
        (void)discard{0,((
          load(is, ts)
        ),void(),0)...};
      }
    }

int main()
{
    std::stringstream ss;
    ss << "1 0 1 2 3 hello";
  //  std::cout << has_member_load<Thing&>{} << "\n";
    Thing t;
    Object o;
    std::string hello;
    loading::load_many( ss, t, o, hello );
    std::cout << t.a << ", " << t.b << ", " << hello << "\n";
    std::cout << o.a << o.b << o.c << "\n";
}