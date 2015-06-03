#include <type_traits>
#include <utility>

template<class... Ts> struct pack { static constexpr int size() { return sizeof...(Ts); } };

template<int I, class T> struct index_pair {};

template<class Pack, class = std::make_integer_sequence<int, Pack::size()>>
struct paired_list;

template<class... Ts, int... Is>
struct paired_list<pack<Ts...>, std::integer_sequence<int, Is...>> : index_pair<Is, Ts>... {};

template<int I, class T>
T get_helper(index_pair<I, T>);

template<class L, int I>
using get = decltype(get_helper<I>(L{}));

template<int I>
struct min_helper : std::integral_constant<int, I> {};

template<int L, int R>
constexpr min_helper<(L < R ? L : R)> operator,(min_helper<L>, min_helper<R>) { return {}; }

template<int I, int... Is>
constexpr int min_() { return (min_helper<I>{} , ... , min_helper<Is>{}); }

template<int I, int... Is>
struct min : std::integral_constant<int, min_<I, Is...>()> {};

template<class... Ps>
struct zip
{
    using L = paired_list<pack<Ps...>>;
    static constexpr auto Min = min<Ps::size()...>::value;
    
    template<int I>
    using helper2 = pack<get<paired_list<Ps>, I>...>;
    
    template<int... Is>
    static pack<helper2<Is>...> helper(std::integer_sequence<int, Is...>);
    
    using type = decltype(helper(std::make_integer_sequence<int, Min>{}));
};

/* ([a], [b], [c]) => [(a, b, c)]
template<class P1, class P2, class P3>
struct zip;

template<class... T1, class... T2, class... T3>
struct zip<pack<T1...>, pack<T2...>, pack<T3...>>
{
    using type = pack<pack<T1, T2, T3>...>;
};
*/
 
int main()
{
    using expected = pack<pack<int, bool, char>, pack<int, bool, char>, pack<int, bool, char>>;
    using output = zip<pack<int, int, int>, pack<bool, bool, bool>, pack<char, char, char>>::type;
    static_assert(std::is_same<output, expected>{});
}