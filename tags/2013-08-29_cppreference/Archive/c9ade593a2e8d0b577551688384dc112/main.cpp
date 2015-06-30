#include <iostream>
#include <typeinfo>

template <typename Out, typename In>
Out f(In x) {
    std::cout << "f<" << typeid(Out).name() <<
                 ", " << typeid(In).name() <<
                 ">(" << x << ")\n";
    return x;
}

template <typename T>
T f(T x) {
    return f<T, T>(x);
}


int main() {
    f(42);
    f<float>(42);
}