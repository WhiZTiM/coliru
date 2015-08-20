struct A {
    void foo(int) {}
};

struct B {
    void foo(const char*) {}
};

struct C: A, B {};

int main() {
    C().foo(3);
    return 0;
}
