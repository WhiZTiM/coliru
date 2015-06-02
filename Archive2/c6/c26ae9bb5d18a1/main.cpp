#include <functional>
#include <iostream>

namespace std_ext { // http://stackoverflow.com/questions/18519087/why-is-there-no-stdprotect
template <typename T> struct protect_wrapper : T {
    protect_wrapper(const T &t) : T(t) {}
    protect_wrapper(T &&t) : T(std::move(t)) {}
};

template <typename T>
typename std::enable_if<!std::is_bind_expression<typename std::decay<T>::type>::value, T && >::type protect(T &&t) {
    return std::forward<T>(t);
}

template <typename T>
typename std::enable_if<std::is_bind_expression<typename std::decay<T>::type>::value,
                        protect_wrapper<typename std::decay<T>::type> >::type
protect(T &&t) {
    return protect_wrapper<typename std::decay<T>::type>(std::forward<T>(t));
}
}

struct A {
    template <typename H> void call_handler(H handler) { handler(); }
};

struct B {
    struct handler_caller_f {
        typedef void result_type;

        template <typename H> void operator()(B *this_, H handler) const { handler(); }
    };

    template <typename H> void run(H handler) {
        m_a.call_handler(std::bind(handler_caller_f(), this, std_ext::protect(handler)));
    }

    A m_a;
};

struct Test {
    void handler() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

int main() {
    Test t;

    B b;
    b.run(std::bind(&Test::handler, &t));
}
