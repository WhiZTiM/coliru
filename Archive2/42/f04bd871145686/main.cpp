#include <type_traits>

namespace detail {
    enum class enabler {};
}

template <bool Condition>
using EnableIf =
    typename std::enable_if<Condition, detail::enabler>::type;

template<typename... Conds>
struct and_ : std::true_type {};

template<typename Cond, typename... Conds>
struct and_<Cond, Conds...>
        : std::conditional<Cond::value, and_<Conds...>,
        std::false_type>::type {};

template<typename... T>
using areInts = and_<std::is_same<T,int>...>;


template<typename Target, typename... Ts>
using areT = and_<std::is_same<Ts,Target>...>;

static_assert(areT<int,int,int,int>::value,"wat");
static_assert(!areT<int,float,int,int>::value,"wat");


int main()
{
    
}