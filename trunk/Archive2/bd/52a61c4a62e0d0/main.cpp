#include <type_traits>

template<typename...> struct void_ { using type = void; };
template<typename... Ignored> using void_t = typename void_<Ignored...>::type;

template<typename Sfinae, typename Type, typename... Args>
struct bracy_impl: std::false_type {};

template<typename Type, typename... Args>
struct bracy_impl<
    void_t<decltype( Type { std::declval<Args>()... })>
    , Type, Args...
>: std::true_type {};

template<typename Type, typename... Args>
struct bracy: bracy_impl<void, Type, Args...> {};

struct aggr {
    int i, j, k;
};

int main()
{
    static_assert( bracy<aggr, int, int, short>(), "A" );
    static_assert( !bracy<aggr, long, int, int>(), "B" );
}
