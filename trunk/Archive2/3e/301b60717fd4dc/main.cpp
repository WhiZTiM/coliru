struct A
{
    void f()
    {
    }
};

struct B1 : public A
{
};

struct B2 : public A
{
};

struct C : B1, B2
{
    void f() // works
    {
        B1::f();
    }
    using B1::f; // does not work
    using B1::A::f; // does not work as well
};

int main()
{
    C c;
    c.f();

    return 0;
}