template< typename T >
struct Foo
{
    template< T... Ts>
    void bar()
    {
    }
};

int main()
{
    Foo<int> f;
    f.bar<1,2,3>();
}