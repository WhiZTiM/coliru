#include <iostream>
#include <tuple>
#include <utility>

template<typename B, typename C>
struct forEachNArgsImpl;

template<std::size_t... Bs, std::size_t... Cs>
struct forEachNArgsImpl<std::index_sequence<Bs...>,std::index_sequence<Cs...>>
{
    template<std::size_t N, typename TF, typename... Ts>
    static void execN(TF mFn, const std::tuple<Ts...>& mXs)
    {
        mFn( std::get< N + Cs >( mXs )... );
    }
    
    template<typename TF, typename... Ts>
    static void exec(TF mFn, const std::tuple<Ts...>& mXs)
    {
        using swallow = bool[];
        (void)swallow{ (execN< Bs * sizeof...(Cs) >( mFn, mXs ), true)... };
    }
};

template<std::size_t N, typename TF, typename... Ts>
void forEachNArgs(TF mFn, Ts... mXs)
{
    static_assert( sizeof...(Ts) % N == 0, "Wrong number of arguments" );
    forEachNArgsImpl<
        std::make_index_sequence<sizeof...(Ts)/N>,
        std::make_index_sequence<N>
    >::exec(mFn, std::forward_as_tuple( mXs... ) );
}

int main()
{
    int result{0};
    forEachNArgs<2>([&result](auto a1, auto a2)
    {
        result += (a1 * a2);
    }, 2, 4, 3, 6);
    std::cout << result << std::endl;

    // roughly evaluates to:
    //     result += (2 * 4);
    //     result += (3 * 6);
}
