#include <vector>
#include <iostream>

struct Foo {
    int i = 0;
    void f(int i) { std::cout << "f(" << i << ")\n"; }
};

template <class T>
struct Ptr {
    
    // Pointer to member
    template <class M>
    auto &operator ->* (M T::*p) {
        return _ptr->*p;
    }
    
    // Pointer to member function
    template <class R, class... As>
    auto operator ->* (R (T::*fp)(As...)) {
        return [ptr = this->_ptr, fp](As&&... args) {
            return (ptr->*fp)(std::forward<As>(args)...);
        };
    }
    
    T& operator*() { return *_ptr; }
    
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
    
    void (Foo::*fp)(int) = &Foo::f;
    (p->*fp)(31);
    
    int i = 90;
    Ptr<int> ip{&i};
}