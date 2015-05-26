struct Myclass {};

void foo( const Myclass & ) {}

Myclass bar() { return Myclass(); }

int main()              
{
  foo( bar() );  // OK C++03
}
