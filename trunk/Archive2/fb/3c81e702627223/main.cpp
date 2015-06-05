#include <vector>
#include <vector>
#include <iostream>
#include <cstddef>

template <typename T>
struct Foo {

    template <typename Q = T>
    typename std::enable_if<!std::is_void<Q>::value, Q>::type foo() {
        return T{} + T{};
    }
    
    template <typename Q = T>
    typename std::enable_if<std::is_void<Q>::value, Q>::type foo() {
        return;   
    }
};

int main() {
    Foo<void> a;
    a.foo();
    
    Foo<int> b;
    b.foo();
}