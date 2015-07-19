#include <cstdio>
#define printf(a)
#define else
#define if(a) puts(#a);

int main() {
    if (4 < 2)
        printf("4 < 2");
    else
        printf("4 > 2");
}

