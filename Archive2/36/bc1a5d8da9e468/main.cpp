#include <string>
#include <iostream>


class A {
    public:
        A(int n) : n_{n} {} 
        // A() {}
    public:
        struct vip_access;
    private:
        A() {}
        int n_;
};

struct A::vip_access {
    static A call_default() {
        return A();   
    }
};

class B {
    public:
        B(const A& a) : a_(a) {}
    public:
        struct vip_access;
    private:
        B() : a_(A::vip_access::call_default()) {}
        A a_;
};

struct B::vip_access {
    static B call_default() {
        return B();   
    }
};

int main() {
    B b = B::vip_access::call_default();
}

