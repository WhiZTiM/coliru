struct foo { template<typename X> int bar() { return 0; } };

template<typename>
foo f;

template<typename... Xs>
void bar()
{
    int i[] = { f<Xs>.bar()... };
}

int main()
{
    bar<void, void, void>();
}
