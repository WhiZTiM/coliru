#include <cstdio>

struct bit {
    int x: 2;
};

int main()
{
    bit a, b, c;
    a.x = 1; // 01
    b.x = 2; // 10 <-- ultimo bit ativo, logo negativo
    c.x = 3; // 11 <-- ultimo bit ativo, logo negativo
    printf("%d %d %d", a.x, b.x, c.x);
}
