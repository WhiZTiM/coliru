#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

template <typename... Funcs>
struct Fold;

template <>
struct Fold<> {
    template <typename T>
    decltype(auto) operator()(T&& t) {
        return std::forward<T>(t);
    }
};

template <typename Func, typename... Funcs>
struct Fold<Func, Funcs...> {
    template <typename T>
    decltype(auto) operator()(T&& t, const Func& func, const Funcs&... funcs) {
        return Fold<Funcs...>{}(func(std::forward<T>(t)), funcs...);
    }
};

template <typename T, typename... Funcs>
decltype(auto) fold(T&& t, const Funcs&... funcs) {
    return Fold<Funcs...>{}(std::forward<T>(t), funcs...);
}


std::string foo(int i) {
    return boost::lexical_cast<std::string>(i + 1) ;
}

int bar(const std::string& s) {
    return boost::lexical_cast<int>(s) + 2;
}

std::string baz(int i) {
    return boost::lexical_cast<std::string>(i * 2) ;
}


int main() {
    std::string s = fold(10, foo, bar, baz);
    std::cerr << s << std::endl;
}