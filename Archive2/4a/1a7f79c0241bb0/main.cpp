
template<typename T>
struct Foo
{
    void DoStuff()    {}
    int GetSomeStuf() { return 42; }
};

template struct Foo<int>;

int main()
{}
