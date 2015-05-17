#include <iostream>
#include <typeinfo>
#include <functional>

template <typename T>
class Foo {
public:
    Foo<T>(T a, T b, T c) :
        a(a),
        b(b),
        c(c) {}
    
    int get() const {return a;}
    
private:
    T a, b, c;
};

int main() {
    Foo<int> foo(1,2,3);
    Foo<float> foob(1.0,2.0,3.0);
    auto lambda = [&, foo](int i){return i + foo.get();};
    
    std::function<int(int)> func = lambda;
    
    std::cout << sizeof(lambda) << std::endl;
    std::cout << sizeof(func) << std::endl;
    
    std::cout << sizeof(typeid(lambda)) << std::endl;
    std::cout << sizeof(typeid(func)) << std::endl;
    return 0;
}