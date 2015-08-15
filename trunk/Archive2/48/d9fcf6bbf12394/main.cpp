#include <iostream>
int a(int m)
{
    return ++m;
}
int b(int &m)
{
    return ++m;
}
int c(int &m)
{
    return ++m;
}

int main()
{
    int p = 0, q = 0, r = 0;

    int result_of_b_p = b(p);
    p += a(result_of_b_p);

    int result_of_a_q = a(q);
    q += b(result_of_a_q);

    int result_of_c_r = c(r);
    r += a(result_of_c_r);

    std::cout << p << q << r << '\n';
}