#include <vector>
#include <iostream>

struct Foo {
    int i = 0;
};

template <class T>
struct Ptr {
    
    template <class M>
    auto &operator ->* (M T::*p) {
        return _ptr->*p;
    }
    
    T *_ptr = nullptr;
};

int main() {
    int Foo::*ptr = &Foo::i;
    
    // Exhibit 1 : standard iterator ////////////////
    std::vector<Foo> v(1);
    auto ite = v.begin();
    
    //ite->*ptr = 42;   // Does not compile
    (*ite).*ptr = 42;
    
    std::cout << v.front().i << '\n';
    
    // Exhibit 2 : custom class /////////////////////
    Foo foo;
    Ptr<Foo> p{&foo};
    
    p->*ptr = 53;
    
    std::cout << foo.i << '\n';
}