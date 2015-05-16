#include <iostream>
#include <tuple>
#include <cmath>

namespace hash_tuple
{
    
std::size_t hash_combine(std::size_t l, std::size_t r) noexcept
{
    constexpr static const double phi = 1.6180339887498949025257388711906969547271728515625;
    static const double val = std::pow(2ULL, 4ULL * sizeof(std::size_t));
    static const std::size_t magic_number = val / phi;
    
    l ^= r + magic_number + (l << 6) + (l >> 2);
    return l;
}
    
template <typename TT>
struct hash
{
    std::size_t operator()(TT const& tt) const
    {                                              
        return std::hash<TT>()(tt);                                 
    }                                              
};

namespace
{
    template <class TupleT, std::size_t Index = std::tuple_size<TupleT>::value - 1ULL>
    struct HashValueImpl
    {
        static std::size_t apply(std::size_t seed, TupleT const& tuple)
        {
            seed = HashValueImpl<TupleT, Index - 1ULL>::apply(seed, tuple);
            seed = hash_combine(seed, std::get<Index>(tuple));
            
            return seed;
        }
    };

    template <class TupleT>
    struct HashValueImpl<TupleT, 0ULL>
    {
        static std::size_t apply(size_t seed, TupleT const& tuple) noexcept
        {
            seed = hash_combine(seed, std::get<0>(tuple));
            return seed;
        }
    };
}

template <typename ... TT>
struct hash<std::tuple<TT...>> 
{
    std::size_t operator()(std::tuple<TT...> const& tt) const
    {                                              
        std::size_t seed = 0;                             
        seed = HashValueImpl<std::tuple<TT...> >::apply(seed, tt);    
        return seed;                                 
    }                                              
};
}

template<typename T, typename TT = typename std::remove_reference<T>::type, size_t... I>
auto
reverse_impl(T&& t, std::index_sequence<I...>)
-> std::tuple<typename std::tuple_element<sizeof...(I) - 1 - I, TT>::type...>
{
    return std::make_tuple(std::get<sizeof...(I) - 1 - I>(std::forward<T>(t))...);
}

template<typename T, typename TT = typename std::remove_reference<T>::type>
auto
reverse(T&& t)
-> decltype(reverse_impl(std::forward<T>(t),
                        std::make_index_sequence<std::tuple_size<TT>::value>()))
{
    return reverse_impl(std::forward<T>(t),
                        std::make_index_sequence<std::tuple_size<TT>::value>());
}

int main()
{
    auto t0 = std::make_tuple(1, 2, 3, 4, 5, 6);
    auto t1 = std::make_tuple(6, 5, 4, 3, 2, 1);
    
    using hash_tuple::hash;
    auto hasher = hash<decltype(t0)>();
    
    std::size_t t0hash = hasher(t0);
    std::size_t t1hash = hasher(t1);
    
    std::size_t t0hsah = hasher(reverse(t0));
    std::size_t t1hsah = hasher(reverse(t1));

    std::cout << hash_tuple::hash_combine(t0hash, t1hash) << "\n" << hash_tuple::hash_combine(t1hsah, t0hsah);
    
    return 0;
}