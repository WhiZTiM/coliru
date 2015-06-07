#include <iostream>

template<typename Value, typename Cascade>
struct Cascader {
    Cascader(Value value, Cascade &cascade) : value_(value), cascade_(cascade) {}
    
    operator Value() {return value_;}
    operator Cascade &() {return cascade_;}
    
    Cascade *operator->() {return &cascade_;}
    
private:
    Value value_;
    Cascade &cascade_;
};

struct Foo {
    auto setA(int a) {
        return Cascader<int, Foo>{a, *this};
    }
    
    auto setB(int b) {
        return Cascader<int, Foo>{b, *this};
    }
};

int main() {
    Foo foo;
    
    std::cout << "foo.setA(23) returns " << foo.setA(23) << '\n';
    std::cout << "foo.setA(10)->setB(20) returns " << foo.setA(10)->setB(20) << '\n';
}