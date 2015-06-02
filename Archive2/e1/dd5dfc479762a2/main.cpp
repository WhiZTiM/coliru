struct A
{
   struct B {};
   B& b;

   A(B& b) : b(b) {}
};

int main()
{
    A::B b ;
    A a(b);
}