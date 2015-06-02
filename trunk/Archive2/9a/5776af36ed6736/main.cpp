class A
{
   struct B {};
   B&& b;

public:
   A() : b(B()) {}
};

int main()
{
    A a;
}