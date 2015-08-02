#include <iostream>

int main()
{
    float a = 1, b = 0 ;
    double c = 1, d = 0 ;
    long double e = 1, f = 0 ;

    std::cout << b/b << ' ' << d/d << ' ' << f/f << '\n' // 0.0/0 NaN
              << a/b << ' ' << c/d << ' ' << e/f << '\n'  // 1.0/0 infinity
              << -a/b << ' ' << -c/d << ' ' << -e/f << '\n' ; // -1.0/0 negative infinity
}
