template<typename Arg>
struct foo {
    using type = typename foo<Arg*>::type;
};

template<typename T> struct foo<T*>;

template<typename Arg>
int bar()
{
    return typename foo<Arg>::type {};
}

extern template int bar<int>();

int main()
{
    return bar<int>();
}

template<typename T>
struct foo<T*> { using type = int; };

template int bar<int>();