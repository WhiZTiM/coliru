struct Bar
{
    Bar(int = 0) {}
};

struct Foo
{
    Bar b;
};

int main()
{
    Foo f;
}