#include <vector>
#include <vector>
#include <iostream>
#include <cstddef>

template <typename T>
struct Foo {

    typename std::enable_if<!std::is_void<T>::value, T>::type foo() {
        return T{} + T{};
    }
    
    typename std::enable_if<std::is_void<T>::value, T>::type foo() {
        return;   
    }
};

int main() {
    Foo<void> a;
    a.foo();
    
    Foo<int> b;
    b.foo();
}