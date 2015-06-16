#include <iostream>

struct A {
    int val;
    A() : val() {}
    A(int _) : val(_) {}
};

struct B : public virtual A {
    B(int _) : A(_) {}
};

struct C : public virtual A {
    C(int _) : A(_) {}
};

struct D : public B, C {
    D(int _) : B(_+1), C(_+2) {}
};

int main() {
    D d = D(1);
    std::cout << d.val << std::endl;
    
    return 0;
}
