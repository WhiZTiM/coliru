struct BaseT< template int X >
{
    void foo() { }
};

struct Derive : BaseT<42>
{
    void bar() { foo(); }
};

int main()
{
}
