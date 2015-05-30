#include <type_traits>

template<class T>
struct some_trait : std::false_type {};

// never called in an evaluated context
template<class T>
some_trait<T> has_some_trait(T);

namespace detail
{

template<class T, class C = decltype(has_some_trait(T{}))>
using check_trait_t = std::enable_if_t<C::value, int>;

} // detail::

int main(){}