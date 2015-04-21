#include <type_traits>
#include <vector>
#include <cstddef>
#include <iostream>

namespace detail {
    template<class T, class U>
    using forwarded_type = std::conditional_t<std::is_lvalue_reference<T>::value, std::remove_reference_t<U>&, std::remove_reference_t<U>&&>;
}
template<class T, class U>
detail::forwarded_type<T,U> forward_like(U&& u) {
    return std::forward<detail::forwarded_type<T,U>>(std::forward<U>(u));
}

struct X {};
void f(X&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
void f(X&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

template <typename Vector>
void g(Vector&& v, std::size_t i) {
  f(forward_like<Vector>(v[i]));
}

int main(){
    g(std::vector<X>{{},{}}, 0);
    auto p = std::vector<X>{{},{}};
    g(p, 0);
}