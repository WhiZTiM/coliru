#include <iostream>
#include <type_traits>
#include <utility>
#include <array>
#include <cstddef>
#include <unordered_map>
using std::size_t;

namespace hash_tuple{
  template <typename TT>
  struct hash {
    size_t operator()(TT const& tt) const {                                              
        return std::hash<TT>()(tt);                                 
    }                                              
  };

  template <class T>
  inline void hash_combine(std::size_t& seed, T const& v) {
    seed ^= hash_tuple::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }
  
  namespace details {
    // Recursive template code derived from Matthieu M.
    template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
    struct HashValueImpl {
      void operator()(size_t& seed, Tuple const& tuple)const{
        HashValueImpl<Tuple, Index-1>{}(seed, tuple);
        hash_combine(seed, std::get<Index>(tuple));
      }
    };
    template <class Tuple>
    struct HashValueImpl<Tuple,0> {
      void operator()(size_t& seed, Tuple const& tuple)const{
        hash_combine(seed, std::get<0>(tuple));
      }
    };
  }

  template <typename ... TT>
  struct hash<std::tuple<TT...>> {
    size_t operator()(std::tuple<TT...> const& tt) const {                                              
      size_t seed = 0;                             
      details::HashValueImpl<std::tuple<TT...> >{}(seed, tt);    
      return seed;                                 
    }                                              
  };
}

struct wrap {};

template<class Sig, class F>
struct memoizer;
template<class R, class...Args, class F>
struct memoizer<R(Args...), F> {
  using base_type = F;
private:
  F base;
  using tup=std::tuple<std::decay_t<Args>...>;
  std::unordered_map<tup, R, hash_tuple::hash<tup> > cache;
public:

  template<class... Ts>
  R operator()(Ts&&... ts) const
  {
    auto args = std::make_tuple(ts...);
    auto it = cache.find( args );
    if (it != cache.end())
      return it->second;

    auto&& retval = base(*this, std::forward<Ts>(ts)...);

    cache.emplace( std::move(args), retval );

    return decltype(retval)(retval);
  }
  template<class... Ts>
  R operator()(Ts&&... ts)
  {
    auto args = std::tie(ts...);
    auto it = cache.find( args );
    if (it != cache.end())
      return it->second;

    auto&& retval = base(*this, std::forward<Ts>(ts)...);

    cache.emplace( std::move(args), retval );

    return decltype(retval)(retval);
  }

  memoizer(memoizer const&)=default;
  memoizer(memoizer&&)=default;
  memoizer& operator=(memoizer const&)=default;
  memoizer& operator=(memoizer&&)=default;
  memoizer() = delete;
  template<typename L>
  memoizer( wrap, L&& f ):
    base( std::forward<L>(f) )
  {}
};

template<class Sig, class F>
memoizer<Sig, std::decay_t<F>> memoize( F&& f ) { return {wrap{}, std::forward<F>(f)}; }

auto fib_base = [](auto&& fib, size_t n)->size_t {
  if (n<=1) return 1;
  return fib(n-1)+fib(n-2);
};

auto fib = memoize< size_t(size_t) >( fib_base );

int main() {
  for (size_t i = 0; i < 20; ++i) {
    std::cout << fib(i) << ',';
  }
  std::cout << '\n';
}