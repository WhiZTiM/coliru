
struct Test
{
    void func() {}
};

struct Foo
{
    void bar() {}
    void (Test::*ptr)();
};

int main()
{
    Foo f;
    f.ptr = &Test::func;
//    f.ptr = &Foo::bar;    // will not compile, void(Foo::*)() cannot be converted to void(Test::*)()
}
