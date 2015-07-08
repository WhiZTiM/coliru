#include <iostream>
#include <typeinfo>

class A {
public:
    virtual void f() {
        std::cout << "A" << std::endl;
    }
};

class B : public A {
public:
    virtual void f() override {
        if (typeid(*this) == typeid(B)) {
            std::cout << "nope";
        }
    }
};

int main() {
    A* obj = new A;
    A* other = new B;
    obj->f();
    other->f();
    return 0;
}