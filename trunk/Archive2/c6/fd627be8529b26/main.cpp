    struct A {};
    struct B {
        B(A a) {}
    };
    int main() {
        B obj(A());
        obj;
    }