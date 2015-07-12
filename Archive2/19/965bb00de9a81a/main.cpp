#include <type_traits>
#include <iostream>

struct Base {
    int i;
};

struct Derived : Base {
    Derived() : j(44) { }
    int j;
};

template<int& i> int f() { return i;}

int main(int argc, char** argv) {
    std::aligned_storage_t<sizeof(Derived), alignof(Derived)> s[1];
    
    Derived* p = reinterpret_cast<Derived*>(s);
    
    new (p) Base();
    p->i = 42;
    new (p) Derived();
    
    std::cout << p->i << " " << p->j << "\n";
    return 0;
}