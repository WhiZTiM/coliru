template<unsigned N>
class Foo;

Foo<0> *p; //implicit instantiation, static_assert doesn't fail

int boo( Foo<0> * ) { return 3; }

int n = boo( nullptr );
int m = boo( p );

Foo<0> q; //explicit instantiation, compilation fails
