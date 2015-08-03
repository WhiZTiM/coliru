struct Foo
{
    Foo() = default;
    explicit Foo(const Foo&) = default;
    int m;
};

int main()
{
    Foo bar;
    Foo foo{bar}; // error here
}
