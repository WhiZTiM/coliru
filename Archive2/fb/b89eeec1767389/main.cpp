#include <iostream>

struct CountedBase {
    void decRef() {}
};

struct Incomplete;
struct Complete : CountedBase {};

template <std::size_t> struct size_tag;

template <class T>
void decRef(T *ptr, size_tag<sizeof(T)>*) {
    std::cout << "static\n";
    static_cast<CountedBase*>(ptr)->decRef();
}

template <class T>
void decRef(T *ptr, ...) {
    std::cout << "reinterpret\n";
    reinterpret_cast<CountedBase*>(ptr)->decRef();
}

template <class T>
struct Handle {
    ~Handle() {
        decRef(m_ptr, nullptr);
    }
    
    T *m_ptr = nullptr;
};

int main() {
    Handle<Incomplete> h1;
    Handle<Complete> h2;
}