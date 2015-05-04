template<class T>
struct A
{
    void foo(){ }
    void bar(){ }
};

int main()
{
    A<int> *a = new A<int>;
    a -> foo();
}