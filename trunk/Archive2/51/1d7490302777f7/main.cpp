struct A
{
   struct B {};
   B&& b;
   
   A()
     : b(B())
   {};
};

int main()
{
    A a;
}