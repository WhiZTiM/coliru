template <typename T>
struct Foo
{
    Bar<T> b;
};

template <typename T>
struct Bar
{
    Bar(int = 0) {}
};

int main()
{
    Foo<char> f;
}