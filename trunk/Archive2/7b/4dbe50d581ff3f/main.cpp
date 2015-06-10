#include <utility>

template<typename,typename> struct apply_indices_impl;

template<typename T,template<T...> class C,T... Ns>
struct apply_indices_impl<C<>,std::integer_sequence<T,Ns...>>
{
    using type = C<Ns...>;
};

template<typename T,typename I> using apply_indices = typename apply_indices_impl<T,I>::type;

template<std::size_t... Ns> struct zip {};

int main()
{
    static_assert( std::is_same< apply_indices<zip<>,std::make_index_sequence<3>>, zip<0,1,2>>::value, "Oops" );
}
