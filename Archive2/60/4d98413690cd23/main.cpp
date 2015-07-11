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

struct neverdelete {
    template <class T>
    void operator()(T *) const {
        throw std::runtime_error("fuck you");
    }
};

int main() {
    std::unique_ptr<A, neverdelete> smartie(new A(4));
}
