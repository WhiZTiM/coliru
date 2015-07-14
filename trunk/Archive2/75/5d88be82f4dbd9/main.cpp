/*
    So a decorator in Python is essentially something like:

    @decorator
    def f(args): pass

    is equivalent to:

    def f(args): pass
    f = decorator(f)

    So it essentially 'augments' a function giving it extra capabilities.
    Usually these decorators are wrappers:

    def decorator(func):
        def wrapped(args):
            print('Hello World!')
            return func(args)
        return wrapped

    @decorator
    def f(args):
        print('arg is ' + str(args))

    And then calling f(10) would print 'Hello World' first and then 'arg is 10'.

    When multiple decorators are in effect, e.g.:

    @one
    @two
    def f(arg): pass

    The equivalent to:

    f = two(one(f))

    This here is an implementation in C++ based on this principle, without the sugar.
*/

#include <tuple>
#include <cstddef>
#include <type_traits>

template<size_t... I>
struct indices {
    using type = indices;
};

template<typename Left, typename Right>
struct concat;

template<size_t... I, size_t... J>
struct concat<indices<I...>, indices<J...>> : indices<I..., (J + sizeof...(I))...> {};

template<size_t N>
struct build_indices : concat<typename build_indices<N / 2>::type, typename build_indices<N - N / 2>::type> {};

template<>
struct build_indices<0> : indices<> {};

template<>
struct build_indices<1> : indices<0> {};

namespace detail {
template<typename Tuple>
struct decorator_helper;

template<typename... Functions>
struct decorator_helper<std::tuple<Functions...>> {
private:
    std::tuple<Functions...> functions;
    static constexpr auto size = sizeof...(Functions);
    using size_type = decltype(size);

    template<size_type Index>
    using counter = std::integral_constant<size_type, Index>;
public:
    decorator_helper(std::tuple<Functions...> f): functions(std::move(f)) {}

    template<size_type Index, typename Function>
    auto augment(counter<Index>, Function&& function) const
    -> decltype(augment(counter<Index + 1>{}, std::get<Index>(functions)(std::forward<Function>(function)))) {
        return augment(counter<Index + 1>{}, std::get<Index>(functions)(std::forward<Function>(function)));
    }

    template<typename Function>
    auto augment(counter<size - 1>, Function&& function) const
    -> decltype(std::get<size - 1>(functions)(std::forward<Function>(function))) {
        return std::get<size - 1>(functions)(std::forward<Function>(function));
    }

    template<typename Function>
    auto operator()(Function&& function) const -> decltype(augment(counter<0>{}, std::forward<Function>(function))) {
        return augment(counter<0>{}, std::forward<Function>(function));
    }
};

template<typename T>
struct identity {
    using type = T;
};

template<typename List, typename T>
struct push_front {};

template<template<typename...> class S, typename... Args, typename T>
struct push_front<S<Args...>, T> : identity<S<T, Args...>> {};

template<typename List>
struct pop_back {};

template<template<typename...> class S>
struct pop_back<S<>> : identity<S<>> {};

template<template<typename...> class S, typename T>
struct pop_back<S<T>> : identity<S<T>> {};

template<template<typename...> class S, typename T, typename... Args>
struct pop_back<S<T, Args...>> : identity<typename push_front<typename pop_back<S<Args...>>::type, T>::type> {};

template<size_t... Indices, typename Tuple>
inline auto tuple_subset(const Tuple& tuple, indices<Indices...>) -> decltype(std::make_tuple(std::get<Indices>(tuple)...)) {
    return std::make_tuple(std::get<Indices>(tuple)...);
}
} // detail

template<typename... Functions>
inline auto decorate(Functions&&... functions) {
    auto&& args = std::make_tuple(std::forward<Functions>(functions)...);
    constexpr auto indices = sizeof...(Functions) - 2 == 0 ? 1 : sizeof...(Functions) - 2;
    auto&& function_tuple = detail::tuple_subset(args, build_indices<indices>{});
    detail::decorator_helper<typename std::remove_reference<decltype(function_tuple)>::type> helper(function_tuple);
    return helper(std::get<sizeof...(Functions) - 1>(args));
}

#include <iostream>

int main() {
    auto decorator = [](auto func) {
        return [func](auto&&... args) { std::cout << "Hello World!\n"; func(args...); };
    };

    auto f = decorate(decorator, [](auto arg) { std::cout << "arg is " << arg << '\n'; });
    f(10);
}
