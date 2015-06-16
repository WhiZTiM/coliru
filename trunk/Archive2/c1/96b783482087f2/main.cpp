#include <iostream>

int dbg(int x, char const *mesg) {
    std::cout << mesg << std::endl;
    return x;
}

struct A {
    int val;
    A() : val() { dbg(0, "A::A()"); }
    A(int _) : val(_) { dbg(0, "A::A(int)"); }
};

struct B : public virtual A {
    B(int _) : A(dbg(_, "B::A()")) { dbg(0, "B::B()"); }
};

struct C : public virtual A {
    C(int _) : A(dbg(_, "C::A()")) { dbg(0, "C::C()"); }
};

struct D : public B, C {
    D(int _) : B(dbg(_+1, "D::B()")), C(dbg(_+2, "D::C()")) { dbg(0, "D::D()"); }
};

int main() {
    D d = D(1);
    std::cout << d.val << std::endl;
    
    return 0;
}
