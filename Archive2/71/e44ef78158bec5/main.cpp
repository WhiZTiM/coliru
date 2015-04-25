#include <type_traits>
#include <typeinfo>
#include <iostream>

namespace detail
{
    template<typename...>
    using void_t = void;
    
    template<typename T,typename=void>
    struct is_metafunction : std::false_type {};
    
    template<typename T>
    struct is_metafunction<T, void_t<typename T::type>> : std::true_type {};
}

template<typename T>
using is_metafunction = detail::is_metafunction<T>;

template<typename F>
using eval_metafunction = typename F::type;


//Examples
template<typename T, typename U>
using have_common_type = is_metafunction<std::common_type<T,U>>;

static_assert(have_common_type<int,char>::value,"");
static_assert(std::is_same<eval_metafunction<std::common_type<int,char>>, int>::value,"");

int main(){}
