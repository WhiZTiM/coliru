template<class T>
struct A
{
    void foo(){ }
    void bar(){ }
};

int main()
{
    A *a = new A;
    a -> foo();
}