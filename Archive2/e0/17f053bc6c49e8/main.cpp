#include <stdio.h>
#include <inttypes.h>
 
int main(void) {
    printf("%zu\n", sizeof(intptr_t));
    printf("%s\n", PRId64);
    printf("%+"PRId64"\n", INTPTR_MIN);
    printf("%+"PRId64"\n", INTPTR_MAX);
 
    intptr_t n = 7;
    printf("%+"PRId64"\n", n);

    return 0;
}