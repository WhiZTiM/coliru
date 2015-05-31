struct A {
    A() = default;
    A(const float& x, const float& y, const float& z, const float& w) { }
};

union {
    float f[4 * 4];
    A a[4];
} u;