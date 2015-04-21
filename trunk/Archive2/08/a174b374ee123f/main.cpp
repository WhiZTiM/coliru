#include <type_traits>
#include <vector>
#include <cstddef>
#include <iostream>

template<class T, class U>
struct forward_like_helper { using type = std::remove_reference_t<U> &&; };

template<class T, class U>
struct forward_like_helper<T&, U> { using type = std::remove_reference_t<U> &; };

template<class T, class U>
typename forward_like_helper<T,U>::type forward_like(U&& u) {
    return static_cast<typename forward_like_helper<T,U>::type>(u);
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