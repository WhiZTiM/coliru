struct X {};
struct Y {};

template <class A, class B, class C>
A doFoo(const B &val)
{
    return {};
}

struct ParticularC {};

template <class A, class B>
constexpr auto myDoFoo = &doFoo<A, B, ParticularC>;

int main()
{
    myDoFoo<X, Y>(Y{});
}
