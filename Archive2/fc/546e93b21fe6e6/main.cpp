struct test
{
    template<class T>
    test(T t) {}
};

int main()
{
    test t(5);
}