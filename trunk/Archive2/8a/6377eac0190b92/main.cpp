struct Outer {
    class C {};
    void f() {}
    class Inner {
       friend class C;
       friend void f();
       static int const i = 0;
    };
};
class C { static int const k = Outer::Inner::i; };
void f() { int i = Outer::Inner::i; }
