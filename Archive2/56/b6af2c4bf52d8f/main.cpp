struct A
{
    void f()
    {
    }
};

struct B1 : public A
{
   using A::f;
};

struct B2 : public A
{
};

struct C : B1, B2
{
    using B1::f; // will work now
};

int main() {
  C c;
  c.f();
}
