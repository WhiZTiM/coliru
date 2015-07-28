#include <stdio.h>
#include <stdint.h>

int main() {
    float f = 1.0;
    printf("%p\n%p\n", (void*)&f, (void*)&((uint16_t*)&f)[1]);
    return 0;
}