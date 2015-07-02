
struct B;
struct A {
    int i;
    A() : i{} {}
    A(B b);
};

struct B {
    B(A a) {i = a.i;}
    int i;
};

A::A(B b) {
    i = b.i;
}

int main () {
    A a;
    B b = a;
}

