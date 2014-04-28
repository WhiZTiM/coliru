#include <type_traits>

namespace std
{
    template<class T, T... vals> struct integer_sequence {};
}

namespace details
{
    template<typename T>
    struct minus_helper;
    template<typename T, T val>
    struct minus_helper< std::integral_constant<T, val> >
    {
        using type = std::integral_constant<T, val-1>;
    };
    
    template<typename T>
    using minus = typename minus_helper<T>::type;
    
    template<typename Int, typename C, Int P, Int... N>
    struct increasing_integer_range :
        increasing_integer_range<Int, minus<C>, P+1, N..., P>
    {};

   /* template<typename Int, Int C, Int P, Int... N>
    struct decreasing_integer_range:
        decreasing_integer_range<Int, C+1, P-1, N..., P>
    {};*/

    template<typename Int, Int P, Int... N>
    struct increasing_integer_range<Int, std::integral_constant<Int, 0>, P, N...>:
        std::integer_sequence<Int, N...>
    {};

    /*template<typename Int, Int P, Int... N>
    struct decreasing_integer_range<Int, 0, P, N...>:
        std::integer_sequence<Int, N...>
    {};*/
}

template<typename Int, Int S, Int E,  bool Increasing=(S<E)>
struct integer_range;

template<typename Int, Int S, Int E>
struct integer_range<Int, S, E, true>:
    details::increasing_integer_range<Int, std::integral_constant<Int, E-S>, S>
{};

/*template<typename Int, Int S, Int E>
struct integer_range<Int, S, E, false>:
    details::decreasing_integer_range<Int, std::integral_constant<Int, E-S>, S>
{};*/

template<std::size_t S, std::size_t E>
using index_range = integer_range<std::size_t, S, E>;

int main()
{
    using my_range = index_range<1, 5>;
}