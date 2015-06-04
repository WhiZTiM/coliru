#include <tuple>
#include <iostream>  
#include <ostream>

template<typename Type>
struct inner_context;

template<class Derived>
struct base {
    using children_type = typename inner_context<Derived>::type;
    const std::tuple<int, children_type> children;

    base(int a, char b) : children(5, children_type{ a, b }) {}
};

struct derived;

template<>
struct inner_context<derived> {
    using type = std::tuple<char, int>;
};

struct derived : public base<derived> {
    derived() : base(10,'x') {}
};

int main(int argc, char* argv[]) {}