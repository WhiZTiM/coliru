enum Foo
{
    FOO,
    BAR
};

enum Bar {
    OOF,
    RAB
};

template<Foo foo, Bar bar>
class FooTemplate
{
public:
    static const int RESULT;
};

template <Bar bar>
class FooTemplate<Foo::FOO, bar>
{
public:
    static const int RESULT;
};

template <Bar bar>
const int FooTemplate<Foo::FOO, bar>::RESULT = int(bar);

template <Bar bar>
class FooTemplate<Foo::BAR, bar>
{
public:
    static const int RESULT;
};

template <Bar bar>
const int FooTemplate<Foo::BAR, bar>::RESULT = 0;

int main()
{
    
}
