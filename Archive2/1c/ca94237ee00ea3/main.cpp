struct Foo
{
    Foo() = default;
    Foo(const Foo&) = default;
};

int main()
{
    Foo x;
    Foo y{x}; // error here
}