#include <iostream>
#include <string>

struct T {
    virtual 
    T* clone() { std::cout << "T::clone()\n"; return this; }
};

struct A : public T {
    
    virtual 
    T* clone() { std::cout << "T::clone()\n"; return this; }    
};

struct B : public T {};

int main() {
    A a;
    B* b;
    
    T& t = a;
    std::cout << "tag 1\n";
//    a = b;
//        a.operator=(  b)
    b = t.clone(       );
    std::cout << "tag 2\n";
    
}