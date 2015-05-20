struct Foo {
    struct {
        void f();
    } b;
};

void Foo::decltype(Foo::b)::f(){}

int main() {
    Foo o;
    o.b.f();
}