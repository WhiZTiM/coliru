#include <iostream>

void foo(int x) {
    std::cout << x;
}

template<typename F, F* P>
struct FunctionPointerToType {
    template<typename... T>
    auto operator()(T... t) {
        return P(t...);
    }
};

int main() {
    FunctionPointerToType<decltype(foo), foo> obj;
    obj(42);
}