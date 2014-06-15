#include <iostream>
#include <typeinfo>

#define UNSAFE_EQ(X) \
friend bool equals(Base &a, Base &b); \
virtual bool unsafeEq(const Base &o) { \
    return *this == static_cast<const X &>(o); \
}

struct Base {
    bool operator==(Base) { return true; }
    virtual ~Base() = default;
    
private:
    UNSAFE_EQ(Base)    
};

struct Derived : Base {
    Derived(int i) : i(i) {}
    bool operator==(Derived d) { return i == d.i; }
    int i;
    
private:
    UNSAFE_EQ(Derived)
};

bool equals(Base &a, Base &b) {
    if(typeid(a) != typeid(b)) return false;
    return a.unsafeEq(b);
}

int main() {
    Base a;
    Derived b{2};
    Derived c{2};
    Derived d{3};
    
    std::cout
            << equals(a, b) << '\n'
            << equals(b, c) << '\n'
            << equals(c, d) << '\n'
            << equals(c, a) << '\n';
}
