template <int X>
struct Base
{
    void foo() { }
};

template <int X>
struct Derive : Base<X>
{
    void bar() { foo(); }
};

int main()
{
}
