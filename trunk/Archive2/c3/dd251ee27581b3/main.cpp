struct A {};

template <typename T>
double operator+(T, double d) { return d; }

//template <typename T>
//double operator+(double d, T) { return d; }


 void test()
 {
    A a;
    double x{};

    double y = a + x;
    double z = x + a;
    (void)y;
    //(void)z;
 }

int main()
{
    test();
}