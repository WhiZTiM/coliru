#include <stdio.h>
#include <stdlib.h>

int main() {
    _Decimal128 x = rand();
    printf("%f", (float)x);
    return 0;
}