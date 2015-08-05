#include <iostream>

struct CountedBase {
    void decRef() {
        std::cout << "decRef\n";
    }
};

template <class T>
struct incomplete {
    void decRef() {
        std::cout << "reinterpret, ";
        reinterpret_cast<CountedBase*>(this)->decRef();
    }
};

template <class T>
struct Handle {
    ~Handle() {
        m_ptr->decRef();
    }
    
    T *m_ptr = nullptr;
};

struct Foo;
struct Bar : CountedBase {};
struct Baz {};

int main() {
    Handle<incomplete<Foo>> h1;
    Handle<Bar> h2;
    //Handle<Baz> h3;
}