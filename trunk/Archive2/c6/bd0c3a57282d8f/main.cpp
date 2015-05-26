struct Myclass {};

void foo( Myclass && ) {}

Myclass bar() { return Myclass(); }

int main()              
{
  foo( bar() ); // OK C++11
}
