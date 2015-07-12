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
    
    auto myDeleter = [](A*) {throw std::runtime_error("Lol bruh.");};
    
    std::unique_ptr<A, decltype(myDeleter)> smartie{new A(4), myDeleter};
}
