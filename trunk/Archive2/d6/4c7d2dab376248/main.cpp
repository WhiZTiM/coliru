#include <stdio.h>

int main(int argc, char** argv) {
    const char* s = "test";
    printf("%d\n", sizeof(*s));
    return 0;
}