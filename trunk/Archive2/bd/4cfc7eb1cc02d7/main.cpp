namespace N
{
    struct A {};

    template <typename T>
    double operator+ (T a, double d) {return d;}

    template <typename T>
    double operator+ (double d, T a) {return d;}
 }

 void test()
 {
    N::A a;
    double x = 10;

    double y = a + x;
    double z = x + a;
 }