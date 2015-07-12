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

void neverdelete(A *) {
    throw std::runtime_error("fuck you");
}

int main() {
    std::unique_ptr<A, std::function<void(A*)>> smartie(new A(4), neverdelete);
}
