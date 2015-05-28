#ifndef ATCH_TYPE_LIST_HPP
#define ATCH_TYPE_LIST_HPP

#include <cstddef>
#include <utility>

namespace atch {
  template<std::size_t N>
  using ic = std::integral_constant<std::size_t, N>;

  template<std::size_t... Ns>
  using iseq = std::index_sequence<Ns...>;

  template<std::size_t N>
  using make_iseq = std::make_index_sequence<N>;

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  template<class... Ts>
  struct type_list {
    using size_type = std::size_t;

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    static constexpr size_type size () { return sizeof... (Ts); }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    template<size_type Idx>
    struct at {
      template<class T>
      struct wrapper { using result = T; };
      
      template<size_type N, class U, class... Us>
      struct access_helper
      {
          using result = typename std::conditional_t<
            (Idx == N), wrapper<U>, access_helper<N+1, Us...>
          >::result;
      };

      using result = typename access_helper<0, Ts..., void>::result;
    };

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    template<class... Us>
    struct push {
      using result = type_list<Ts..., Us...>;
    };

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    template<size_type Idx, class U>
    struct set {
      struct wrapper { using result = U; };
      
      template<size_type N>
      struct access_helper
      {
          using result = typename std::conditional_t<N!=Idx, at<N>, wrapper>::result;
      };

      template<size_type... Ns>
      static auto set_helper (iseq<Ns...>)
        -> type_list<typename access_helper<Ns>::result...>
      { }

      using result = decltype (set_helper (make_iseq<size()> ()));
    };

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    struct init {
      template<size_type... Ns>
      static auto helper (iseq<Ns...>) -> type_list<typename at<Ns>::result...>; 

      using result = decltype (helper (make_iseq<size ()-1> ()));
    };
  };

} /* namespace atch */

#endif /* include guard */

#ifndef ATCH_META_COUNTER_HPP
#define ATCH_META_COUNTER_HPP

#include <cstddef>

namespace atch {
  struct meta_counter {
    template<std::size_t N>
    struct ident {
      friend constexpr std::size_t adl_lookup (ident<N>);
      static constexpr std::size_t value = N;
    };

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    template<class Ident>
    struct writer {
      friend constexpr std::size_t adl_lookup (Ident) {
        return Ident::value;
      }

      static constexpr std::size_t value = Ident::value;
    };
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    template<std::size_t N, class = char[noexcept(adl_lookup(ident<N> ()))?+1:-1]>
    static constexpr std::size_t value_reader (int, ident<N>) {
      return N;
    }

    template<std::size_t N>
    static constexpr std::size_t value_reader (float, ident<N>, std::size_t R = value_reader (0, ident<N-1> ())) {
      return R;
    }

    static constexpr std::size_t value_reader (float, ident<0>) {
      return 0;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    template<std::size_t Max = 32>
    static constexpr std::size_t value (std::size_t R = value_reader (0, ident<Max> ())) {
      return R;
    }

    template<std::size_t N = 1, class H = meta_counter, int C = H::value ()>
    static constexpr std::size_t next (std::size_t R = writer<ident<N + C>>::value) {
      return R;
    }
  };
}

#endif /* include guard */

#ifndef ATCH_META_LIST_HPP
#define ATCH_META_LIST_HPP

#include <cstddef>

namespace atch {

  struct meta_list {
    using counter = atch::meta_counter;

    template<std::size_t N>
    struct ident {
      friend auto adl_lookup (ident<N>);
      friend auto adl_lookup (ident<N!=0?99999+N:0>) {
          return type_list<> {};
      }
      static constexpr std::size_t value = N;
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

    template<class State, class H = meta_list, int C = H::counter::next (), class Ident = typename H::template ident<C>>
    static constexpr std::size_t push_state (std::size_t R = writer<Ident, State>::value) {
      return R;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    template<class H = meta_list, std::size_t N = H::counter::value ()>
    using value_ident = typename H::template ident<N>;

    template<class H = meta_list, class Ident = typename H::template value_ident<>>
    using value = decltype (adl_lookup (Ident ()));

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

template<class T>
void force_linker_diagnostic ();

#include <iostream>

int main () {
  using LX = atch::meta_list;

  LX::push<void, void, void,void> ();
  LX::set<0, int> ();
  LX::set<2, float> ();
  LX::pop ();
  force_linker_diagnostic<LX::value<>> ();
}