struct A {
    A() = default;

};

union {
    int i;
    A a;
} u;