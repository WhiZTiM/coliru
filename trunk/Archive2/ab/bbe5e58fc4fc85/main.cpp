#include <cstdio>
#define a(a) b(a)
#define b(a) #a
#define if(a) puts(#a);
#define printf(x)
#define else

int main() {
    if (4 < 2)
        printf("4 < 2");
    else
        printf("4 > 2");
}

