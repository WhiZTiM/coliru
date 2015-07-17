#include <sstream>
#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include <vector>
#include <tuple>
#include <algorithm>

    template<class It> using it_value_type =
      typename std::iterator_traits<It>::value_type;
    template<class It> using it_reference =
      typename std::iterator_traits<It>::reference;

    template<class It>
    struct range_t {
      It b, e;
      range_t():b(),e(){}
      range_t(It s, It f):b(s),e(f){}
      template<class C, class=std::enable_if_t<!std::is_same<std::decay_t<C>,range_t>{}>>
      range_t(C&& c):
        range_t(std::begin(c),std::end(c))
      {}
      It begin() const { return b; }
      It end() const { return e; }

      bool empty() const { return begin()==end(); }
      it_reference<It> front() const { return *begin(); }
      it_reference<It> back() const { return *std::prev(end()); }

      range_t pop_front() const {
        if (empty()) return {};
        else return {std::next(begin()), end()};
      }
    };

    template<class C, class It=std::decay_t<decltype(std::begin(std::declval<C&>()))>>
    range_t<It> range( C&& c ) {
      return {std::begin(c), std::end(c)};
    }

    bool all_of( std::initializer_list<bool> il ) {
      return std::all_of( il.begin(), il.end(), [](bool b){return b;} );
    }

    template<class Sink, class Operator, class...Its>
    Sink transform( Sink sink, Operator op, range_t<Its>... srcs ) {
      while(!all_of({srcs.empty()...})) {
        *sink++ = op( (srcs.empty()?it_value_type<Its>{}:srcs.front())... );
        using discard=int[];
        (void)discard{0,
          ((srcs = srcs.pop_front()),0)...
        };
      }
      return sink;
    }

    template<class Sink, class Operator, class...Srcs>
    Sink transform( Sink sink, Operator op, Srcs&&... srcs ) {
      return transform( sink, op, range(srcs)... );
    }

int main() {
    std::vector<int> result;
    std::vector<int> a = {1,2,3};
    std::vector<int> b = {1,2};
    transform( std::back_inserter(result), [](int a, int b){return a+b;}, a, a );
    for (int x:result)
        std::cout << x << '\n';
    result.clear();
    transform( std::back_inserter(result), [](int a, int b){return a+b;}, a, b );
    for (int x:result)
        std::cout << x << '\n';    
}