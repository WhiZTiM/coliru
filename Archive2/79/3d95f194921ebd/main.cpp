#include <type_traits>
#include <limits>
#include <cstdint>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

/////////////////////////////////////////////////////////////////
// safe_signed_range

template <
    std::intmax_t MIN,
    std::intmax_t MAX
>
struct safe_signed_range {
};

/////////////////////////////////////////////////////////////////
// safe_unsigned_range

template <
    std::uintmax_t MIN,
    std::uintmax_t MAX
>
struct safe_unsigned_range {
};

template<class T, class U>
using calculate_max_t = typename boost::mpl::if_c<
    std::numeric_limits<T>::is_signed
    || std::numeric_limits<U>::is_signed,
    std::intmax_t,
    std::uintmax_t
>::type;

template<typename Integer, Integer Top, Integer Bottom>
struct defer_unsigned_lazily {
    using type = safe_unsigned_range<Top, Bottom>;
};

template<typename Integer, Integer Top, Integer Bottom>
struct defer_signed_lazily {
    using type = safe_signed_range<Top, Bottom>;
};
    

template<typename T, typename U>
struct test {

    typedef calculate_max_t<T, U> max_t;
    static_assert(std::is_same<max_t, std::intmax_t>::value, "unexpected value for max_t");
    static_assert(std::is_signed<max_t>::value, "check parameter");

/*
    typedef typename boost::mpl::if_c<
        std::is_signed<max_t>::value,
        safe_signed_range<std::numeric_limits<max_t>::min(), std::numeric_limits<max_t>::max()>,
        safe_unsigned_range<std::numeric_limits<max_t>::min(), std::numeric_limits<max_t>::max()>
    >::type type;
*/
    using limits = std::numeric_limits<max_t>;
    typedef typename boost::mpl::eval_if_c<
        std::is_signed<max_t>::value, 
        defer_signed_lazily<max_t, limits::min(), limits::max()>, 
        defer_unsigned_lazily<max_t, limits::min(), limits::max()>
    >::type type;
};

test<int, int> t1;
//test<int, unsigned> t2;
//test<unsigned, int> t3;
//test<unsigned, unsigned> t4;

int main(){
    return 0;
}