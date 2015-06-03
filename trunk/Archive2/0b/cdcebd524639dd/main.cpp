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

int main()
{
    return bar<int>();
}

// program is wrong: at this point of instantiation foo<T>::type will not terminate
template int bar<int>();

template<typename T>
struct foo<T*> { using type = int; };