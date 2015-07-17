template<unsigned N>
class Foo
{
 static_assert(N > 0, "Min 1 for N");
};

Foo<0> *p; //implicit instantiation, static_assert doesn't fail

int boo( Foo<0> * ) { return 3; }

int n = boo( nullptr );
int m = boo( p );

Foo<0> q; //explicit instantiation, compilation fails
