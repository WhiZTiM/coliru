template<typename X, typename Y> struct foo {};

template<typename X, typename Y> void operator<<(foo<X, Y>, X) {}
template<typename X, typename Y> void operator<<(foo<X, Y>, char) {}

int main()
{
    foo<char, struct dummy> f;
    f << 'a';
}