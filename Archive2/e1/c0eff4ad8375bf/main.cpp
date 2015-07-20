class Base
{
public:
    void doStuff() {}
};

class Derived : private Base
{
public:
    // Using older access declaration (without using) shoots a warning
    // and results in the same compilation error
    using Base::doStuff;
};

template<class C, typename Func>
void exec(C *c, Func func)
{
    (c->*func)();
}

int main()
{
    Derived d;
    // Until here, everything compiles fine
    d.doStuff();
    // For some reason, I can't access the function pointer
    exec(&d,&Derived::doStuff);
}