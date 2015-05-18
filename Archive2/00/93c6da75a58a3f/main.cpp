#include <string.h>
#include <stdio.h>

int f();

int main(void) {
    printf("f(1, 2, 3) = %d", f(1, 2, 3));
}

int f(x, y, z) int x; int y; int z; { return x + y + z; }
