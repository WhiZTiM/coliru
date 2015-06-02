#include <iostream>

template<typename T>
class Base {
public:
    // It doesn't matter if the types are dependent on T or not
    typedef int NestedDef;
    typedef T NestedDefOnT;
    float field;
};

class Derived : public Base<float> {
public:
    void x() {
        NestedDef nd; (void)nd;
        NestedDefOnT ndt; (void)ndt;
        field = 0.0f;
    }
};

template<typename T>
class Derived2 : public Base<int> {
public:
    void y() {
        NestedDef nd; (void)nd;
        NestedDefOnT ndt; (void)ndt;
        field = 0.0f;
    }
};

template<typename T>
class Derived3 : public Base<T> {
public:
    void z() {
        NestedDef nd; (void)nd;
        NestedDefOnT ndt; (void)ndt;
        field = 0.0f;
    }
};

template<typename T>
class Derived3Ok : public Base<T> {
public:
    void z() {
        typename Derived3Ok::NestedDef nd; (void)nd;
        typename Derived3Ok::NestedDefOnT ndt; (void)ndt;
        this->field = 0.0f;
        Derived3Ok::field = 0.0f;
    }
};

int main() {}
