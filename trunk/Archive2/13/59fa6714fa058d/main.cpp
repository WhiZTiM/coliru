#ifndef ATCH_META_LIST_HPP
#define ATCH_META_LIST_HPP

#include <cstddef>

#include "type_list.hpp"
#include "meta_counter.hpp"

namespace atch {

  template<class Tag>
  struct meta_list {
    using counter = atch::meta_counter<meta_list<Tag>>;

    template<std::size_t N, class = void>
    struct ident {
      friend auto adl_lookup (ident<N>);

      static constexpr std::size_t value = N;
    };

    template<class T>
    struct ident<0, T> {
      friend auto adl_lookup (ident<0>) {
        return type_list<> {};
      }

      static constexpr std::size_t value = 0;
    };

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    template<class Ident, class Value>
    struct writer {
      friend auto adl_lookup (ident<Ident::value>) {
        return Value {};
      }

      static constexpr std::size_t value = Ident::value;
    };
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    template<class State, class H = meta_list, class Ident = typename H::template ident<H::counter::next ()>>
    static constexpr std::size_t push_state (std::size_t R = writer<Ident, State>::value) {
      return R;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    template<class H = meta_list, std::size_t N = H::counter::value ()>
    using value_ident = typename H::template ident<N>;

    template<class H = meta_list, class Ident = typename H::template value_ident<>>
    using value = decltype (adl_lookup (Ident {}));

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    template<class... Ts, class H = meta_list>
    static constexpr void push (
      std::size_t = push_state<typename H::template value<>::template push<Ts...>::result > ()
    ) { } 

    template<class H = meta_list>
    static constexpr void pop (
      std::size_t = push_state<typename H::template value<>::init::result > ()
    ) { }

    template<std::size_t Idx, class T, class H = meta_list>
    static constexpr void set (
      std::size_t = push_state<typename H::template value<>::template set<Idx, T>::result > ()
    ) { }
  };
}

#endif /* include guard */