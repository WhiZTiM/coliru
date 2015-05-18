#include <iostream>
#include <string>

template <typename... F> struct overload;

template <class F1, class... F>
struct overload <F1, F...> : F1, overload<F...> {
    overload(F1 f1, F... f) : F1(f1), overload<F...>(f...) {}

    using F1::operator();
    using overload<F...>::operator();        
    
};

template <class F>
struct overload <F> : F {
    overload(F f) : F(f) {}
    using F::operator();
};

template <class F...>
auto make_overload(F... f) {
    return (f)...;
}

int main() {
    auto f1 = [](int i) {return 0;};
    auto f2 = [](float f) {return 1.0f;};
    auto f3 = [](std::string str) {return "Hello world!";};
    
    auto fn = make_overload(f1, f2, f3);
    
    std::cout << fn(1) << std::endl;
    std::cout << fn(2.0) << std::endl;
    std::cout << fn("three") << std::endl;
    
    return 0;
}