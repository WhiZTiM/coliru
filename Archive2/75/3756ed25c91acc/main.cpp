#include <iostream>
#include <memory>
#include <utility>

template <int I>
struct foo {
    static void
    show() {
        std::cout << I << '\n';
    }
};

struct foo_proxy {
    virtual void show() = 0;
};

template <int I>
struct foo_proxy_impl : foo_proxy {
    virtual void
    show() {
        foo<I>::show();
    }
};

template <typename>
struct make_proxies;

template <int... Is>
struct make_proxies<std::integer_sequence<int, Is...>> {
    static std::unique_ptr<foo_proxy> value[sizeof...(Is)];
};

template <int... Is>
std::unique_ptr<foo_proxy>
make_proxies<std::integer_sequence<int, Is...>>::value[sizeof...(Is)]{std::make_unique<foo_proxy_impl<Is>>()...};

auto& proxies = make_proxies<std::make_integer_sequence<int, 30>>::value;

int
main() {
    proxies[rand() % 30]->show();
}
