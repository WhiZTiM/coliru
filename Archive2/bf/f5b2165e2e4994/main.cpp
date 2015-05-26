struct Myclass {};

void foo( Myclass & ) {}

Myclass bar() { return Myclass(); }

int main()              
{
  Myclass mc;        // no temporary object
  foo( mc = bar() );   // OK C++03
}
