class A {
protected:
    struct B { };
};
struct D: A::B, A { };