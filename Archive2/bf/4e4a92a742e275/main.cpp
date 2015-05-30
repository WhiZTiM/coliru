#include <type_traits>

template<class T>
struct some_trait : std::false_type {};

template<class T>
struct some_other_trait : std::false_type {};

// never called in an evaluated context
template<class T, class = std::enable_if_t<some_other_trait<T>::value>>
some_trait<T> has_some_trait(T);

namespace detail
{

template<class T, class C = decltype(has_some_trait(T{}))>
using check_trait_t = std::enable_if_t<C::value, int>;

} // detail::

template<class T, class = detail::check_trait_t<T>>
void foo(T){}

#include <iostream>

struct X{};

std::true_type has_some_trait(X);

int main()
{
    foo(X{});
}