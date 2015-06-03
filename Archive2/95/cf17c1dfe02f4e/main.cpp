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

template<typename Arg>
int requires()
{ return bar<Arg>(); }

template int requires<int>();

int main()
{
    return requires<int>();
}

template<typename T>
struct foo<T*> { using type = int; };

template int bar<int>();