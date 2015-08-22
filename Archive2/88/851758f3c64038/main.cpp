
#include <type_traits>

enum Foo {
    FOO,
    BAR
};

enum Bar {
    OOF,
    RAB
};

template<Foo /*foo*/, Bar /*bar*/>
struct FooValue;

template<Bar bar>
struct FooValue<Foo::FOO, bar>
    : std::integral_constant<int, bar> { };

template<Bar bar>
struct FooValue<Foo::BAR, bar>
    : std::integral_constant<int, 0> { };

template<Foo foo, Bar bar>
class FooTemplate
    : public FooValue<foo, bar>
{
};

int main()
{
    static_assert(!FooTemplate<FOO, OOF>::value, "Check");
    static_assert(FooTemplate<FOO, RAB>::value, "Check");

    static_assert(!FooTemplate<BAR, OOF>::value, "Check");
    static_assert(!FooTemplate<BAR, RAB>::value, "Check");
}
