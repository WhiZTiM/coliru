#include <future>
#include <tuple>
#include <iostream>
#include <unistd.h>

template <typename T>
std::future<T> f(T& t) {
    return std::async(std::launch::async, [=]{
        for(int i = 0; i < t; ++i) {
            sleep(1);
            std::cout << t << '\n';
        }
        return t;
    });
}

template <typename... T>
void g(T&&... t) {
    std::cout << "g\n";
}

template <class T, std::size_t... Idx>
void callG(T &tuple, std::index_sequence<Idx...>) {
    g(std::get<Idx>(tuple).get()...);
}

template <typename... T>
void call_wrapper(T&&... t) {
    auto results = std::make_tuple(f(t)...);
    callG(results, std::index_sequence_for<T...>{});
}

int main() {
    call_wrapper(2, 4, 5);
    return 0;
}