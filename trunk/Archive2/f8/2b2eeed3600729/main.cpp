#include <type_traits>

namespace N
{
    struct A {};

    template <typename T, typename = std::enable_if_t<std::is_class<T>{}>>
    double operator+ (T a, double d) {return d;}

    template <typename T, typename = std::enable_if_t<std::is_class<T>{}>>
    double operator+ (double d, T a) {return d;}
 }

 void test()
 {
    N::A a;
    double x{0.0};

    double y = a + x;
    double z = x + a;
 }
 
int main()
{
    test();
}