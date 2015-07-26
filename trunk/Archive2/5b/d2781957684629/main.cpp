#include <stdio.h>

typedef struct sfClock sfClock;

int main() {
    sfClock * clock = 0;
    printf("%p", (void*)clock);
    return 0;
}
