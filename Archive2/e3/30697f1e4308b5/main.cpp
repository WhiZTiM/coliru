class Foo
{
  public:
    static struct Bar {
      bool a = true;
      int b = 69;
    } bar;
};

Foo::Bar Foo::bar;

int main()
{
  Foo::bar.a = false;
}