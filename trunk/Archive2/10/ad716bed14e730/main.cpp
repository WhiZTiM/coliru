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
    
    ~A() {
        delete ptr;
    }
    
    int* ptr;
};

int main() {
    std::unique_ptr<A> smartie (4, [] {
        throw std::runtime_error("Lol bruh.");
    });
}
