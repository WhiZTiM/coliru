struct B
{
};

struct A
{
    A(B *)  {}
};

int main()
{
    A a = new B();
}