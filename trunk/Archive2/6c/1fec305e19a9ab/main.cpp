#include <type_traits>
#include <iostream>

struct Base {
    Base() : i(42) { }
    int i;
};

struct Derived : Base {
    Derived() : j(44) { }
    int j;
};

template<int& i> int f() { return i;}

int main(int argc, char** argv) {
    void* p = ::operator new(sizeof(Derived));
    
    Base* b = static_cast<Base*>(p);
    Derived* d = static_cast<Derived*>(p);
    
    new (b) Base();
    std::cout << b->i << "\n"; // At this stage we only care about i being valid.
    b = nullptr;
    new (d) Derived();
    std::cout << d->i << " " << d->j << "\n"; // Now i and j should be valid.
    
    return 0;
}