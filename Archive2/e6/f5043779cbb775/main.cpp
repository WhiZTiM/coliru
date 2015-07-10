struct Outer {
    void f() {}
    class Inner {
        friend void f();
        static const int i = 0;
    };
};
void f() { int i = Outer::Inner::i; }
