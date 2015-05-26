#include <cstdio>

struct A {
    unsigned char x:1;
};

int main()
{
    A a;

    printf("sizeof(A) = %u\n", sizeof(A));

    a.x = 0; printf("a.x = %u\n", a.x);
    a.x = 1; printf("a.x = %u\n", a.x);
    a.x = 2; printf("a.x = %u\n", a.x);
    a.x = 3; printf("a.x = %u\n", a.x);
    a.x = 4; printf("a.x = %u\n", a.x);
}
