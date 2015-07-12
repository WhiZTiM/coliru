#include <iostream>
#include <memory>

class A {
public:
    A(int i) {
        ptr = new int(i);
    }
    
    int operator()() {
        return *ptr;   
    }
    
    ~A() = delete;
    
    int* ptr;
};

int main() {
    std::unique_ptr<A, std::function<void(A*)>> smartie(new A(4), [](auto *) {
        throw std::runtime_error("fuck you");
    });
}
