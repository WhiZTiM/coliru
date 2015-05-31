#include <tuple>

template <typename F, typename... As>
using meta_apply = typename F::template apply<As...>;

template <typename... Ts>
struct typelist {
    template<size_t N>
    using get = std::tuple_element_t<N, std::tuple<Ts...>>;
    static constexpr size_t size = sizeof...(Ts);
};

template<class T, size_t N> using id = T;
template<class T, class Seq> struct repeat_c;
template<class T, size_t...Ns> struct repeat_c<T, std::index_sequence<Ns...>>{
    using type = typelist<id<T,Ns>...>;
};
template<class T, size_t N> using repeat = typename repeat_c<T, std::make_index_sequence<N>>::type;

template<class L>
struct typelist_indexer {
    template<size_t N, class T> struct helper_base { using type = T; };
    template<class S, class> struct helper;
    template<size_t... Ns, class... Ts> 
    struct helper<std::index_sequence<Ns...>, typelist<Ts...>> : helper_base<Ns, Ts>... {};
    
    template<size_t N, class T>
    static helper_base<N, T> do_get(helper_base<N,T>);
    
    using helper_type = helper<std::make_index_sequence<L::size>, L>;
    
    template<size_t N>
    using get = typename decltype(do_get<N>(helper_type()))::type;
    
};

template<class, class, class...>
struct typelist_transform_helper;

template<size_t... Ints, class F, class...Lists>
struct typelist_transform_helper<std::index_sequence<Ints...>, F, Lists...>{
    template <class MF, size_t N, typename... Ls>
#ifdef USE_INDEXER
    using apply_to_Nth = meta_apply<MF, typename typelist_indexer<Ls>::template get<N>...>;
#else
    using apply_to_Nth = meta_apply<MF, typename Ls::template get<N>...>;
#endif
    using type = typelist<apply_to_Nth<F, Ints, Lists...>...>;
};

template<class F, class L1, class... Lists>
struct typelist_transform : typelist_transform_helper<std::make_index_sequence<L1::size>, F, L1, Lists...> {
    // static assert on size of all lists being equal if wanted
};

struct make_tuple_type {
    template<class... Ts>
    using apply = std::tuple<Ts...>;
};

  using T = typelist_transform<make_tuple_type, repeat<int, LIST_SIZE>, repeat<long, LIST_SIZE>, repeat<double, LIST_SIZE>>::type; 
  T t;
int main(){

}