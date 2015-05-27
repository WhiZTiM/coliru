#include <tuple>

template <typename F, typename... As>
using meta_apply = typename F::template apply<As...>;

template <typename... Ts>
struct typelist {
    template<size_t N>
    using get = std::tuple_element_t<N, std::tuple<Ts...>>;
    static constexpr size_t size = sizeof...(Ts);
};

template<class, class, class...>
struct typelist_transform_helper;

template<size_t... Ints, class F, class...Lists>
struct typelist_transform_helper<std::index_sequence<Ints...>, F, Lists...>{
    template <class MF, size_t N, typename... Ls>
    using apply_to_Nth = meta_apply<MF, typename Ls::template get<N>...>;
    
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

template<class> class TD;
int main(){
  using T = typelist_transform<make_tuple_type, typelist<int, char, long>, typelist<double, float, short>, typelist<long long, unsigned, wchar_t>>::type; 
  TD<T> t;
}