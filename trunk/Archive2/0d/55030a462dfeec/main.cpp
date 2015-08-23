#include <iostream>
#include <utility>
#include <tuple>
#include <cstddef>
#include <type_traits>

struct Noisy
{
    Noisy() { std::cout << "Noisy()" << std::endl; }
    Noisy(const Noisy&) { std::cout << "Noisy(const Noisy&)" << std::endl; }
    Noisy(Noisy&&) { std::cout << "Noisy(Noisy&&)" << std::endl; }
    ~Noisy() { std::cout << "~Noisy()" << std::endl; }
    Noisy& operator=(const Noisy&) { std::cout << "operator=(const Noisy&)" << std::endl; return *this; }
    Noisy& operator=(Noisy&&) { std::cout << "operator=(Noisy&&)" << std::endl; return *this; }
};

template <typename T>
auto explode(T&& t, char)
{
    return std::forward_as_tuple(std::forward<T>(t));
}

template <typename T, std::size_t I = std::tuple_size<std::decay_t<T>>{}>
auto explode(T&& t, int);

template <typename T, std::size_t... Is>
auto explode(T&& t, std::index_sequence<Is...>)
{
    return std::tuple_cat(explode(std::get<Is>(std::forward<T>(t)), 0)...);
}

template <typename T, std::size_t I>
auto explode(T&& t, int)
{
    return explode(std::forward<T>(t), std::make_index_sequence<I>{});
}

template <typename T, std::size_t... Is>
auto decay_tuple(T&& t, std::index_sequence<Is...>)
{
    return std::make_tuple(std::get<Is>(std::forward<T>(t))...);
}

template <typename T>
auto decay_tuple(T&& t)
{
    return decay_tuple(std::forward<T>(t), std::make_index_sequence<std::tuple_size<std::decay_t<T>>{}>{});
}

template <typename T, std::size_t... Is>
auto merge_tuple(T&& t, std::index_sequence<Is...>)
{
    return decay_tuple(std::tuple_cat(explode(std::get<Is>(std::forward<T>(t)), 0)...));
}

template <typename T>
auto merge_tuple(T&& t)
{
    return merge_tuple(std::forward<T>(t), std::make_index_sequence<std::tuple_size<std::decay_t<T>>{}>{});
}

// Tests:

template <typename T> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

int main()
{
    std::tuple<std::tuple<std::tuple<std::tuple<Noisy, Noisy>>>, std::tuple<std::tuple<Noisy>>> t;
    
    auto x = merge_tuple(t);
    TD<decltype(x)>();
}
