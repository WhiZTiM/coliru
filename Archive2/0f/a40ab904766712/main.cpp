void foo(int, char, bool) {}

template <typename F>
void bar(F f)
{
    f(1, '2', true);
}

int main()
{
    bar<decltype(foo)>(foo);
}