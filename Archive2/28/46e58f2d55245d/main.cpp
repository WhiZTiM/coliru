#include <utility>
#include <cstddef>
#include <type_traits>
#include <tuple>
#include <iostream>

using size_t=std::size_t;

template<size_t K, class indexes>
struct offset_indexes;
template<size_t K, size_t...Is>
struct offset_indexes<K, std::index_sequence<Is...>>:
  std::index_sequence<(K+Is)...>
{};

// SFINAE test optional, but why not:
template<class F, class...Ts, size_t... Is>
std::result_of_t< F( std::tuple_element_t< Is, std::tuple<Ts&&...> >... ) >
call_with_some( F&& f, std::index_sequence<Is...>, Ts&&... ts ) {
  return std::forward<F>(f)(
    std::get<Is>(
      std::forward_as_tuple(std::forward<Ts>(ts)...)
    )...
  );
}

template<class F, size_t n>
struct call_by_n {
  F&& f;
  template<size_t...Offset, class...Args>
  void operator()(std::index_sequence<Offset...>, Args&&...args) {
    static_assert(0==(sizeof...(Args)%n), "Number of args must be divisible by n");
    using indexes = std::make_index_sequence<n>;
    using discard=int[];

    (void)discard{0,(
        ( call_with_some( f, offset_indexes<Offset*n, indexes>{}, std::forward<Args>(args)...) )
    ,void(),0)...};
    
  }
  void operator()() {} // do nothing, naturally
};

template<size_t n, class F, class...Args>
void forEachNArgs(F&& f, Args&&...args) {
  call_by_n<F,n>{std::forward<F>(f)}(std::make_index_sequence<sizeof...(Args)/n>{}, std::forward<Args>(args)...);
}

int main()
{
    int result{0};
    forEachNArgs<2>([&result](auto a1, auto a2)
    {
        result += (a1 * a2);
    }, 2, 4, 3, 6);
 
    std::cout << result << std::endl;
}