template<unsigned N>
class Foo
{
 static_assert(N > 0, "Min 1 for N");
};


Foo<0> *p; //implicit instantiation, static_assert doesn't fail


Foo<0> q; //explicit instantiation, compilation fails
